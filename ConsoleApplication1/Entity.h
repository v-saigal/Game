#pragma once
#include <string>
#include "Location.h"
#include "Deal.h"
#include <vector>
#include "Position.h"
class Entity
{
	public:
		int id;
		std::string name;
		int health = 10;
		Position position;
		Entity(std::string _name, Position _position, int _entityID);
		void move(int destX, int destY);

};

