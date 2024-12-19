#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <windows.h>
#include <Gdiplus.h>
#include <iostream>
#include <vector>

class Transform{
private:
    std::vector<std::pair<std::string, std::string>> transforms;
public:
    Transform();
    Transform(std::vector<std::pair<std::string, std::string>> transforms);
    std::vector<std::pair<std::string, std::string>> getTransforms() const;
    void print() const;
};

#endif