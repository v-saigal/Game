#pragma once
#include <SDL3/SDL.h>
#include "LTexture.h"

class Sprite
{
public:
    explicit Sprite(LTexture& texture);

    void setPos(float x, float y);
    bool isMoving() const;
    void moveTo(float x, float y);
    void update(float deltaTime);
    void render();

private:
    LTexture& texture;

    float posX{ 0 };
    float posY{ 0 };
    float destX{ 0 };
    float destY{ 0 };

    float speed{ 20.0f }; // pixels/sec
    bool moving{ false };
};
