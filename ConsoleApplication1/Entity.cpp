#include "Entity.h"

Entity::Entity(std::string _name, Position _position, int _entityID)
	: name(_name), position(_position), id(_entityID)
{
}

void Entity::move(int destX, int destY) {
	position.x = destX;
	position.y = destY;
};

