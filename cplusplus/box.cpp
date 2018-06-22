#include <iostream>

using namespace std;

class Box
{
public:
    double length;  //长度
    double width;   
    double height; 

    double getVolume(void);
    void setLength(double len);
    void setWidth(double wid);
    void setHeight(double hei);
};

double Box::getVolume()
{
    return length * width * height;
}

void Box::setLength(double len)
{
    length = len;
}

void Box::setWidth(double wid)
{
    width = wid;
}

void Box::setHeight(double hei)
{
    height = hei;
}

