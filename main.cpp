#include"count.h"

int main()
{
    Geodesy geodesy;
    geodesy.readGfcFile("E:\\文件\\物理大地测量\\EGM2008.gfc");
    geodesy.countE();


    return 0;
}
