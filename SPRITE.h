//
// Created by 73539 on 20.10.2021.
//

#ifndef MAIN_CPP_SPRITE_H
#define MAIN_CPP_SPRITE_H
#include <SFML/Graphics.hpp>

class SPRITE : public sf::Sprite {
private:
    float countFrames;
//    sf::Texture textureAnimation;
    sf::Vector2i rectSize;
    int numberSprites;
public:
    SPRITE(sf::Vector2f position, const sf::Texture& text, const sf::Vector2i rectSize, const int numberSprites);
    virtual void update(float deltaTime);
};


#endif //MAIN_CPP_SPRITE_H
