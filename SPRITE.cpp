//
// Created by 73539 on 20.10.2021.
//

#include "SPRITE.h"
SPRITE::SPRITE(const sf::Vector2f position, const sf::Texture& text, const sf::Vector2i rectSize,
               const int numberSprites)
{
//    textureAnimation.loadFromFile(filename);
    this->setPosition(position);
    this->rectSize = rectSize;
    this->numberSprites = numberSprites;
    this->setTexture(text);
    countFrames = 0;
}
void SPRITE::update(float deltaTime)
{
    this->setTextureRect({rectSize.x * int(countFrames / (60.f / numberSprites)), 0, rectSize.x, rectSize.y});
    countFrames += 1.f * deltaTime;
    if(countFrames >= 60)
        countFrames = 0;
}