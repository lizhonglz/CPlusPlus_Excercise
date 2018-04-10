#include "count.h"

Geodesy::Geodesy()
{

}
//读取.efc文件
void Geodesy::readGfcFile(QString fileAddress)
{
    //打开efc文件
    QFile file;
    file.setFileName(fileAddress);
    if( !file.open( QIODevice::ReadOnly) )
    {
        cout<<"open error"<<endl;
        exit(EXIT_FAILURE);
    }
    QTextStream read(&file);
    QString line=read.readLine();
    //跳过文件头
    while(line.indexOf("end_of_head")<0)
    {
        line=read.readLine();
    }    
    line=read.readLine();
    //读取gfc数据
    Gfc gfc1;
    gfcV.resize(maxOrder+1);
    while(!file.atEnd())
    {
        gfc1.c=line.mid(17,22).toDouble();
        gfc1.s=line.mid(42,22).toDouble();
        gfc1.sigmaC=line.mid(68,16).toDouble();
        gfc1.sigmaS=line.mid(88,16).toDouble();
        int orderL;
        orderL=line.mid(5,4).toInt();
        gfcV[orderL].push_back(gfc1);
        line=read.readLine();
        if(line.mid(5,4).toInt()>maxOrder)
        {
            break;
        }
    }
    file.close();

}
//计算第一,二偏心率e,es(second eccentricity)
void Geodesy::countE(void)
{
    //赋初值
    double J2=-1*sqrt(5)*gfcV[2][0].c;
    e=sqrt(3*J2);
    double eTmp=0,q0;
    //迭代计算
    while(fabs(e-eTmp)>pow(0.1,10))
    {
        eTmp=e;
        es=e/sqrt(1-e*e);
        q0=pow(es,3)*(1-6/7*es*es+5/7*pow(es,4)-20/33*pow(es,6))*2/15;
        e=sqrt(3*J2+(w*w*pow(a,3)*2*pow(e,3))/(GM*15*q0));
    }

}
//计算椭球上的正常重力r0
void Geodesy::countR0()
{
    double b=a*sqrt(1-e*e);                                                      //地球短半径b
    double E=sqrt(a*a-b*b);
    double m=a*a*b*w*w/GM;

    double q0=1/2*((1+3*b*b/E/E)/tan(E/b)-3*b/E);
    double q01=3*(1+b*b/E/E)*(1-b/E/tan(E/b))-1;

    double ra=GM/a/b*(1-m-m/6*es*q01/q0);
    double rp=GM/a/a*(1+m/3*es*q01/q0);

    r0=(b*rp*sin(blh.coorB)*sin(blh.coorB)+a*ra*cos(blh.coorB)*cos(blh.coorB))/
       (sqrt(a*a*cos(blh.coorB)*cos(blh.coorB)+b*b*sin(blh.coorB)*sin(blh.coorB)));

}
//将大地坐标BLH转成大地直角坐标XYZ
void Geodesy::BLHToXYZ(const BLH &blh1, XYZ &xyz1)
{
    double N=a/sqrt(1-e*e*sin(blh1.coorB)*sin(blh1.coorB));
    xyz1.coorX=(N+blh1.coorH)*cos(blh1.coorB)*cos(blh1.coorL);
    xyz1.coorY=(N+blh1.coorH)*cos(blh1.coorB)*sin(blh1.coorL);
    xyz1.coorZ=(N*(1-e*e)+blh1.coorH)*sin(blh1.coorB);

}
//计算待求点极坐标
void Geodesy::countPolar()
{
    polar.l=blh.coorL;
    polar.rl=atan(sqrt(1-e*e)*tan(blh.coorB));
    polar.rv=sqrt(xyz.coorX*xyz.coorX+xyz.coorY*xyz.coorY+xyz.coorZ*xyz.coorZ);

}
