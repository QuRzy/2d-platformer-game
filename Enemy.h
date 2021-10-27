//
// Created by 73539 on 21.10.2021.
//

#ifndef MAIN_CPP_ENEMY_H
#define MAIN_CPP_ENEMY_H
#include <SFML/Graphics.hpp>
#include "VECTOR.h"
#include "Player.h"
#include <cmath>
class Enemy : public sf::Sprite {
private:
    float speed;
    bool isRight;
    float countFrames, countHitFall;
    float coolDown;
    sf::Texture textureIdle, textureRun, textureHit;
    enum State {
        Idle = 0, Run, Hit
    };
    State state;
public:
    Enemy(float positionX = 0, float positionY = 0);
    Enemy(sf::Vector2f position);
    static void initForArray(const std::string level[],VECTOR<Enemy>& array);
    void update(float deltaTime);
    void checkCollision(Player& player,const std::string level[]);
};


#endif //MAIN_CPP_ENEMY_H
