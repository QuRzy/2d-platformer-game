//
// Created by 73539 on 20.10.2021.
//

#ifndef MAIN_CPP_PARTICLE_H
#define MAIN_CPP_PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle : public sf::Sprite {
private:
    float countFrames;
    sf::Texture textureAnimation;
    sf::Vector2i rectSize;
    int numberSprites;
public:
    Particle();
    Particle(sf::Vector2f position,  const sf::Vector2i rectSize, const int numberSprites);
    virtual bool update(float deltaTime);
};


#endif //MAIN_CPP_PARTICLE_H
