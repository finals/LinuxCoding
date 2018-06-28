#include <iostream>

class Box {
private:
    unsigned int length;
    unsigned int width;
    unsigned int height;

public:
    Box(unsigned int length, width, height) : length(length), width(width), height(height) {}
    ~Box() {}
    unsigned int show();
};


unsigned int Box::show() 
{
    return length * width * height;
}

