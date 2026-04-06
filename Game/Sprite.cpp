#include "Sprite.h"
#include <cmath>

Sprite::Sprite(LTexture& texture) : texture(texture) {}

void Sprite::setPos(float x, float y) {
    posX = x;
    posY = y;
    destX = x;
    destY = y;
}
bool Sprite::isMoving() const {
    return moving;
}
void Sprite::moveTo(float x, float y) {
    destX = x;
    destY = y;
    moving = true;
}

void Sprite::update(float deltaTime) {
    if (!moving) return;

    float dx = destX - posX;
    float dy = destY - posY;
 
    float step = speed * deltaTime;

    if (-1.0f < dx && dx < 1.0f) {
        posX = destX;
    }
    else {
        posX += dx/abs(dx)*step;
        return;
    }
    if (-1.0f < dy && dy < 1.0f) {
        posY = destY;
        moving = false;
    }
    else {
        posY += dy / abs(dy) * step;
        return;
    }

}

void Sprite::render() {
    SDL_FRect srcRect{ 0, 0, 32, 32 }; // assuming sprite sheet top-left
    texture.render(posX, posY, &srcRect);
}
