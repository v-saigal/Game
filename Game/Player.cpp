#include "Player.h"

Player::Player()
    : Entity("Player")
{
}

Player::Player(const std::string& name)
    : Entity(name)
{
}

Player::~Player() = default;