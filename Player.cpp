//
// Created by 73539 on 19.10.2021.
//

#include "Player.h"

Player::Player(sf::Vector2f position)
{
    this->setPosition(position);
    textureIdle.loadFromFile("../images/player/Idle.png");
    textureRunning.loadFromFile("../images/player/Running.png");
    textureJumping.loadFromFile("../images/player/Jumping.png");
    textureFalling.loadFromFile("../images/player/Falling.png");
    textureHit.loadFromFile("../images/player/TakingDamage.png");
    textureVictory.loadFromFile("../images/player/VictoryPose.png");
    this->setTexture(textureIdle);
    this->setTextureRect({0, 0, 16, 16});
    this->scale(2,2);
    countFrames = 0;
    isRight = true, isJump = false, isGround = false, isRunning = false, isHit = false, isCanJump = true, isVictory = false;
    speed = 4.f, countJump = 15, countFall = 1;
    soundBufferJump.loadFromFile("../images/jump.wav");
    soundJump.setBuffer(soundBufferJump);
    soundJump.setVolume(12.f);
    soundBufferHit.loadFromFile("../images/hit.wav");
    soundHit.setBuffer(soundBufferHit);
    soundHit.setVolume(12.f);
    soundBufferStomp.loadFromFile("../images/stomp.wav");
    soundStomp.setBuffer(soundBufferStomp);
    soundStomp.setVolume(12.f);
}
void Player::update(float deltaTime)
{
    isRunning = false;
    if(isHit)
        goto hitDetecded;
    if(isVictory)
        goto victoryDetecded;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        isRight = false;
        this->move(-speed * deltaTime, 0);
        isRunning = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        isRight = true;
        this->move(speed * deltaTime, 0);
        isRunning = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGround && isCanJump)
    {
        isJump = true;
        isCanJump = false;
        soundJump.play();
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGround)
    {
        isCanJump = true;
    }
    victoryDetecded:
    if(isJump)
    {
        if(countJump > 0)
        {
            this->move(0, -countJump * deltaTime);
            countJump -= 1.18f * deltaTime;
        }
        else
        {
            countJump = 15;
            isJump = false;
        }
    }
    if(!isJump && !isGround)
    {
        this->move(0, countFall * deltaTime);
        if(countFall <= 8.f)
            countFall += 1.f * deltaTime;
        else
            countFall = 8.f;
    }
    else
        countFall = 1;

    hitDetecded:
    float temp;
    if(isRunning && !isJump && (countFall < 3.2f)) {
        this->setTexture(textureRunning); temp = 10.f; }
    else if(isHit) {this->setTexture(textureHit); temp = 20.f;}
    else if(isJump) {this->setTexture(textureJumping); temp = 60.f; }
    else if(!isGround && countFall >= 3.2f) {this->setTexture(textureFalling); temp = 30.f; }
    else if(isVictory) {this->setTexture(textureVictory); temp = 30.f;}
    else {
        this->setTexture(textureIdle); temp = 15.f; }
    isGround = false;
    if(isRight)
        this->setTextureRect({16 * int(countFrames / temp) ,0,16,16});
    else
        this->setTextureRect({16 * (1 + int(countFrames / temp)),0,-16,16});
    if(isHit)
    {
        this->move(0, countFall * deltaTime);
        if(countFall <= 7.f)
            countFall += 0.15f * deltaTime;
    }
    countFrames += 1.f * deltaTime;
    if(countFrames >= 60)
        countFrames = 0;

}
void Player::checkCollision(const sf::RectangleShape &cube)
{
    float sizeX = 16 * this->getScale().x , sizeY = 16 * this->getScale().y;

    if(this->getGlobalBounds().intersects(cube.getGlobalBounds()))
    {
        int i = -1;
        float min = 100000.1f;
        if(abs( (this->getPosition().y+sizeY) - cube.getPosition().y ) < min)
        {
            min = abs( (this->getPosition().y+sizeY) - cube.getPosition().y );
            i = 2;
        }
        if(abs(this->getPosition().x - (cube.getPosition().x + cube.getSize().x)) < min)
        {
            min = abs(this->getPosition().x - (cube.getPosition().x + cube.getSize().x));
            i = 1;
        }
        if(abs((this->getPosition().x+sizeX) - cube.getPosition().x) < min)
        {
            min = abs((this->getPosition().x+sizeX) - cube.getPosition().x);
            i = 0;
        }
        if(abs( this->getPosition().y - (cube.getPosition().y + cube.getSize().y) ) < min)
        {
            min = abs( this->getPosition().y - (cube.getPosition().y + cube.getSize().y) );
            i = 3;
        }

        switch (i) {
            case 0:
                this->setPosition(cube.getPosition().x - sizeX, this->getPosition().y);
                break;
            case 1:
                this->setPosition(cube.getPosition().x + cube.getSize().x, this->getPosition().y);
                break;
            case 2:
                this->setPosition(this->getPosition().x, cube.getPosition().y - sizeY);
                isGround = true;
                break;
            case 3:
                this->setPosition(this->getPosition().x, cube.getPosition().y + cube.getSize().y);
                isJump = false;
                countJump = 15;
                break;
        }
    }
}
bool Player::getIsHit() const
{
    return isHit;
}
