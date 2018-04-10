#ifndef COUNT_H
#define COUNT_H
#include"preparation.h"
#include<QString>
#include<QFile>
#include<QTextStream>
#include<iostream>
#include<cmath>
const int maxOrder=360;                                           //参与计算的最大阶数
const double w=7.2921150e-5;                                      //地球自转角速度
const double GM=3.986005e+14;                                     //地心引力常数：万有引力常数与地球质量乘积
const double a=6378137.0;                                         //地球长半径

class Geodesy
{
public:
    Geodesy();
    void readGfcFile(QString fileAddress);                        //读取.efc文件
    void countE(void);                                            //计算第一,二偏心率e,es(second eccentricity)
    void countR0(void);                                           //计算椭球上的正常重力r0
    void BLHToXYZ(const BLH&blh1, XYZ&xyz1);                      //将大地坐标BLH转成大地直角坐标XYZ
    void countPolar(void);                                        //计算待求点极坐标
private:

    vector<vector<Gfc> >gfcV;                                     //读取的地球重力场模型系数
    BLH blh;                                                      //待求点大地坐标
    XYZ xyz;                                                      //待求点大地直角坐标
    Polar polar;                                                  //待求点极坐标
    double e,es;                                                  //第一偏心率,第二偏心率(second eccentricity)
    double r0;                                                    //椭球上的正常重力

};

#endif // COUNT_H
