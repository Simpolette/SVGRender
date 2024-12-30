#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <windows.h>
#include <Gdiplus.h>
#include <iostream>
#include <vector>
#include <sstream>

class Transform{
private:
    std::vector<std::pair<std::string, std::string>> transforms;
public:
    Transform();
    Transform(std::vector<std::pair<std::string, std::string>> transforms);
    Gdiplus::Matrix* getMatrix() const;
    void print() const;
};

#endif