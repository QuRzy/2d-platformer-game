//
// Created by 73539 on 21.10.2021.
//

#include "Enemy.h"
Enemy::Enemy(sf::Vector2f position)
{
    this->setPosition(position);
    speed = 4.5f;
    isRight = (rand()%2==1) ? true : false;
    countFrames = 0;
    coolDown = 0;
    state = Idle;
    countHitFall = 0;
    textureIdle.loadFromFile("../images/Enemies/Chicken/Idle.png");
    textureRun.loadFromFile("../images/Enemies/Chicken/Run.png");
    textureHit.loadFromFile("../images/Enemies/Chicken/Hit.png");
}
Enemy::Enemy(float positionX, float positionY)
{
    this->setPosition(positionX, positionY);
    speed = 4.f;
    isRight = (rand()%2==1) ? true : false;
    countFrames = 0;
    coolDown = 0;
    state = Idle;
    countHitFall = 0;
    textureIdle.loadFromFile("../images/Enemies/Chicken/Idle.png");
    textureRun.loadFromFile("../images/Enemies/Chicken/Run.png");
    textureHit.loadFromFile("../images/Enemies/Chicken/Hit.png");
}
void Enemy::update(float deltaTime)
{
    float temp8 = 5;
    if(state == Idle)
        this->setTexture(textureIdle);
    else if(state == Run)
        this->setTexture(textureRun);
    else if(state == Hit && countHitFall == 0)
    {
        this->setTexture(textureHit);
        countFrames = 0;
        temp8 = 12;
    }
    else if(state == Hit)
        temp8 = 12;
    if(isRight)
        this->setTextureRect({32 * (int(countFrames / temp8) + 1) ,0,-32,32});
    else
        this->setTextureRect({32 * int(countFrames / temp8) ,0,32,32});
    if(state == Run)
    {
        coolDown -= 2.4f * deltaTime;
        if(isRight)
            this->move(speed * deltaTime, 0);
        else if(!isRight)
            this->move(-speed * deltaTime, 0);
    }
    if(coolDown <= 0 && state != Hit)
        state = Idle;
    if(state == Hit) {
        this->move(0, countHitFall * deltaTime);
        this->setOrigin(16,16);
        this->rotate(4.f * deltaTime);
        this->setOrigin(0,0);
        if(countHitFall <= 8.f)
            countHitFall += 0.5f * deltaTime;
    }
    countFrames += 1.4f * deltaTime;
    if(countFrames >= 60.f)
        countFrames = 0;
}
void Enemy::initForArray(const std::string level[],VECTOR<Enemy>& array)
{
    for(int i = 0; i < 15; ++i)
    {
        for(int j = 0; j < level[i].size(); ++j)
        {
            if(level[i][j] == 'c')
                array.append({{j * 32.f, i * 32.f}});
        }
    }
}
void Enemy::checkCollision(Player &player,const std::string level[])
{

    if(state == Hit || player.isVictory) return;

    if(!player.isHit) {
        sf::RectangleShape tempEnemy;
        tempEnemy.setSize({25, 30});
        tempEnemy.setPosition(this->getPosition().x + 4.25f, this->getPosition().y + 1.5f);
        if (tempEnemy.getGlobalBounds().intersects(player.getGlobalBounds())) {
            int i = -1;
            float min = 100000.1f;

            if (abs((tempEnemy.getPosition().y + tempEnemy.getSize().y) - player.getPosition().y) < min) {
                min = abs((tempEnemy.getPosition().y + tempEnemy.getSize().y) - player.getPosition().y);
                i = 2;
            }
            if (abs(tempEnemy.getPosition().x - (player.getPosition().x + 32)) < min) {
                min = abs(tempEnemy.getPosition().x - (player.getPosition().x + 32));
                i = 1;
            }
            if (abs((tempEnemy.getPosition().x + tempEnemy.getSize().x) - player.getPosition().x) < min) {
                min = abs((tempEnemy.getPosition().x + tempEnemy.getSize().x) - player.getPosition().x);
                i = 0;
            }
            if (abs(tempEnemy.getPosition().y - (player.getPosition().y + 32)) < min) {
                min = abs(tempEnemy.getPosition().y - (player.getPosition().y + 32));
                i = 3;
            }

            switch (i) {
                case 0:
                    player.isHit = true;
                    player.soundHit.play();
                    player.countFall = 0.f;
                    break;
                case 1:
                    player.isHit = true;
                    player.soundHit.play();
                    player.countFall = 0.f;
                    break;
                case 2:
                    player.isHit = true;
                    player.soundHit.play();
                    player.countFall = 0.f;
                    break;
                case 3:
                    player.isGround = true;
                    player.soundStomp.play();
                    state = Hit;
                    return;
                    break;
            }
        }
    }
    sf::CircleShape leftSphere, rightSphere;
    leftSphere.setRadius(5), rightSphere.setRadius(5);
    leftSphere.setOrigin(leftSphere.getRadius(), leftSphere.getRadius()), rightSphere.setOrigin(rightSphere.getRadius(), rightSphere.getRadius());
    leftSphere.setPosition(this->getPosition().x + 16, this->getPosition().y + 16), rightSphere.setPosition(this->getPosition().x + 16, this->getPosition().y + 16);
    bool isL = true, isR = true;
    for(int d = 0; d < (854 / 2); d+=7)
    {
        if(isL && leftSphere.getGlobalBounds().intersects(player.getGlobalBounds()) && level[int(this->getPosition().y/32) + 1][int((this->getPosition().x+32)/32) - 1] != ' '
         && !player.isJump && player.isGround)
        {
            state = Run;
            isRight = false;
            coolDown = 60;
            return;
        }
        if(isR &&rightSphere.getGlobalBounds().intersects(player.getGlobalBounds()) && level[int(this->getPosition().y/32) + 1][int(this->getPosition().x/32) + 1] != ' '
                 && !player.isJump && player.isGround)
        {
            state = Run;
            isRight = true;
            coolDown = 60;
            return;
        }
        if(level[int(this->getPosition().y/32) + 1][int((this->getPosition().x+32)/32) - 1] == ' ' ||
        level[int(this->getPosition().y/32) + 1][int(this->getPosition().x/32) + 1] == ' ')
            state = Idle;
        if(isL && int(leftSphere.getPosition().x / 32) >= 0 && level[int(leftSphere.getPosition().y / 32)][int(leftSphere.getPosition().x / 32)] == '#')
        {
            float distance = pow(leftSphere.getPosition().x - (this->getPosition().x+16), 2) + pow(leftSphere.getPosition().y - (this->getPosition().y+16), 2);
            distance = sqrt(distance);
            if(distance < 32.f) {
                isRight = true;
                state = Idle;
            }
            isL = false;

        }
        if(isR && int(rightSphere.getPosition().x / 32) <= level[0].size() && level[int(rightSphere.getPosition().y / 32)][int(rightSphere.getPosition().x / 32)] == '#')
        {
            float distance = pow(rightSphere.getPosition().x - (this->getPosition().x+16), 2) + pow(rightSphere.getPosition().y - (this->getPosition().y+16), 2);
            distance = sqrt(distance);
            if(distance < 32.f) {
                isRight = false;
                state = Idle;
            }
            isR = false;

        }
        if(!isL && !isR)
            return;
        leftSphere.move(-7.f, 0);
        rightSphere.move(7.f, 0);
    }
}