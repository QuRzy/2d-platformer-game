//
// Created by 73539 on 20.10.2021.
//

#include "Particle.h"
Particle::Particle()
{}
Particle::Particle(const sf::Vector2f position,  const sf::Vector2i rectSize,
               const int numberSprites)
{
//    textureAnimation.loadFromFile(fl);
    this->setPosition(position);
    this->rectSize = rectSize;
    this->numberSprites = numberSprites;
//    this->setTexture(textureAnimation);
    countFrames = 0;
}
bool Particle::update(float deltaTime)
{
    this->setTextureRect({rectSize.x * int(countFrames / (60.f / numberSprites)), 0, rectSize.x, rectSize.y});
    countFrames += 3.f * deltaTime;
    if(countFrames >= 60) {
        countFrames = 0;
        return true;
    }
    return false;
}