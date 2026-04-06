#pragma once
#include <string>
#include "gGlobal.h"
#include "LConst.h"
class Location
{
public:
	std::string name;
	int xPos;
	int yPos;
	LocationType lType;

	Location(std::string _name, LocationType _lType, int _xPos, int _yPos);

};