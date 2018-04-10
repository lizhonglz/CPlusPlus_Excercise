#ifndef PREPARATION
#define PREPARATION
#include"vector"
using namespace std;
class Gfc
{
public:
    double c,s;                          //地球重力场模型系数
    double sigmaC,sigmaS;                //地球重力场模型系数精度s-sigmaS，c-sigmaC
};

class BLH
{
public:
    double coorB,coorL,coorH;            //大地坐标BLH，纬度，经度，大地高

};
class XYZ
{
public:
    double coorX,coorY,coorZ;            //大地直角坐标，xyz
};
class Polar
{
public:
    double rv,rl,l;                      //rv:向径(radius vector);rl:归化纬度(reduced latitude);l:经度(longitude)

};

#endif // PREPARATION

