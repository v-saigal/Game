#pragma once
#include "Location.h"
#include <vector>
#include <random>
#include "LConst.h"
#include "Position.h"
class Map
{
	public:
		//Size of the map to generate
		Map(int _width, int _height);
		std::vector<std::vector<Location>> grid;
		bool posInBounds(Position pos);
		int width;
		int height;
	private: 

		
		Location& getLocation(int x, int y);
		void mapGen();

};

