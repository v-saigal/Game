#pragma once
#include "Location.h"
class Village :
    public Location
{
    public:
        Village(std::string _name) : Location(_name) {
            tileID = 0;
    }
};

