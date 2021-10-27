//
// Created by 73539 on 19.10.2021.
//

#ifndef INC_2D_PLATFORMER_PLAYER_H
#define INC_2D_PLATFORMER_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Enemy.h"
class Player : public sf::Sprite {
private:
    float speed, countJump, countFall;
    bool isRight, isJump, isGround, isRunning, isHit, isCanJump;
    sf::Texture textureIdle, textureRunning, textureJumping, textureFalling, textureHit, textureVictory;
    float countFrames;
    sf::Sound soundJump, soundHit, soundStomp;
    sf::SoundBuffer soundBufferJump, soundBufferHit, soundBufferStomp;
public:
    bool isVictory;
    Player(sf::Vector2f position);
    void update(float deltaTime);
    void checkCollision(const sf::RectangleShape& cube);
    bool getIsHit() const;
    friend class Enemy;
};


#endif //INC_2D_PLATFORMER_PLAYER_H
