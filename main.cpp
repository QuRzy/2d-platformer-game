#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "SPRITE.h"
#include "Particle.h"
#include "VECTOR.h"
#include "Enemy.h"
#include <ctime>
using namespace std;
string level[] = {
        "                                                       ",
        "                                                       ",
        "              aac                                     v",
        "               ##     a                              ##",
        "             c       ###                         c     ",
        "           ###                           aaa   ####    ",
        "     c  a               c                aaa           ",
        "     ####      ##########               #####          ",
        "            a                                          ",
        "           #                          #                ",
        "                                                       ",
        "            a        aa              #                 ",
        "   aa       #        aa   a                            ",
        "#  aa     ###        c    #     c a #                  ",
        "#############     #####################################"
};
int main()
{
    srand(time(NULL));
    sf::RenderWindow window({1280, 720}, "2d-platformer");
//    window.setFramerateLimit(144);
    sf::View view8;
    view8.reset({0,0,854,480});
    window.setView(view8);
    Player player({view8.getSize().x / 2.f - 250, view8.getSize().y / 2.f});
    sf::Texture textureApple;
    textureApple.loadFromFile("../images/Apple.png");
    SPRITE apple({0,0}, textureApple,{32,32},17);
    apple.scale(1.5,1.5);
    VECTOR<Particle> collecteds;
    sf::Clock clock;
    sf::Texture textureGrassDirtBlock, textureDirtBlock;
    textureGrassDirtBlock.loadFromFile("../images/grassDirtBlock.png");
    textureDirtBlock.loadFromFile("../images/dirtBlock.png");
    sf::Texture t;
    t.loadFromFile("../images/effect/Collected.png");
    sf::Texture textureBackground;
    textureBackground.loadFromFile("../images/Brown.png");
    textureBackground.setRepeated(true);
    sf::Sprite spriteBackGround, spriteBackGround1;
    spriteBackGround.setTexture(textureBackground);
    spriteBackGround1.setTexture(textureBackground);
    spriteBackGround.setTextureRect({0,0,int(view8.getSize().x), int(view8.getSize().y)});
    spriteBackGround1.setTextureRect({0,0,int(view8.getSize().x), int(view8.getSize().y)});
    spriteBackGround1.setPosition(spriteBackGround1.getPosition().x, -view8.getSize().y + 32);
    sf::Texture textureFlag;
    textureFlag.loadFromFile("../images/Flag.png");
    SPRITE flagVictory({0,0},textureFlag, {64,64}, 10);
    VECTOR<Enemy> enemies;
    Enemy::initForArray(level, enemies);
    sf::SoundBuffer soundBufferCoin;
    soundBufferCoin.loadFromFile("../images/newCoin.wav");
    sf::Sound soundCoin;
    soundCoin.setBuffer(soundBufferCoin);
    soundCoin.setVolume(40.f);

    sf::SoundBuffer soundBufferVictory;
    soundBufferVictory.loadFromFile("../images/victory.wav");
    sf::Sound soundVictory;
    soundVictory.setBuffer(soundBufferVictory);
    soundVictory.setVolume(12.f);
    cout << enemies.size() << endl;
    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        cout << 1.f / deltaTime << endl;
        deltaTime *= 60.f;
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

        }


        apple.update(deltaTime);
        for(int i = 0; i < collecteds.size(); ++i)
        {
            if(collecteds[i].update(deltaTime))
            {
                collecteds.erase(i);
            }
        }
        for(int i = 0; i < enemies.size(); ++i)
        {
            enemies[i].checkCollision(player, level);
            enemies[i].update(deltaTime);
            if(enemies[i].getPosition().y > 500.f)
                enemies.erase(i);

        }
        player.update(deltaTime);
        flagVictory.update(deltaTime);
        window.setView(view8);
        view8.setCenter(((player.getPosition().x+16) > (view8.getSize().x / 2.f))  ? (player.getPosition().x+16) : (view8.getSize().x / 2.f) , view8.getSize().y / 2);
        spriteBackGround.move(0, 0.5f * deltaTime);
        spriteBackGround1.move(0, 0.5f * deltaTime);
        if(spriteBackGround.getPosition().y > (view8.getSize().y-32))
            spriteBackGround.setPosition(spriteBackGround.getPosition().x, -view8.getSize().y + 32);
        if(spriteBackGround1.getPosition().y > (view8.getSize().y-32))
            spriteBackGround1.setPosition(spriteBackGround.getPosition().x, -view8.getSize().y + 32);
        window.clear();

        spriteBackGround.setPosition(view8.getCenter().x  - (view8.getSize().x / 2.f), spriteBackGround.getPosition().y);
        spriteBackGround1.setPosition(view8.getCenter().x  - (view8.getSize().x / 2.f), spriteBackGround1.getPosition().y);
        window.draw(spriteBackGround);
        window.draw(spriteBackGround1);
        for(int i = 0; i < 15; ++i)
        {
            for(int j = (((player.getPosition().x - (view8.getSize().x / 2)) / 32) >= 0) ? ((player.getPosition().x - (view8.getSize().x / 2)) / 32): 0;
                j < ( ( ((view8.getCenter().x + (view8.getSize().x / 2)) / 32) < (level[i].size()) ) ?  ((view8.getCenter().x + (view8.getSize().x / 2)) / 32): level[i].size() ); ++j)
            {
                if(level[i][j] == '#')
                {
                    sf::RectangleShape cube;
                    cube.setSize({32, 32});
                    cube.setPosition(j*cube.getSize().x, i*cube.getSize().y);
                    sf::Sprite sCube;
                    if(i!=0 && level[i-1][j] != '#')
                        sCube.setTexture(textureGrassDirtBlock);
                    else
                        sCube.setTexture(textureDirtBlock);
                    sCube.setPosition(j*32, i*32);
                    window.draw(sCube);
                    if(!player.getIsHit())
                        player.checkCollision(cube);
                }
                else if(level[i][j] == 'a')
                {
                    apple.setPosition(j * 32, i * 32);
                    sf::RectangleShape tempCube;
                    tempCube.setSize({32 / 2, 32 / 2});
                    tempCube.setPosition(apple.getPosition().x + 8, apple.getPosition().y + 8);
                    if(player.getGlobalBounds().intersects(tempCube.getGlobalBounds())) {
                        soundCoin.play();
                        level[i][j] = ' ';
                        collecteds.append({apple.getPosition(), {32, 32}, 6});
                        collecteds[collecteds.size()-1].setTexture(t);
                        collecteds[collecteds.size()-1].update(deltaTime);
                    }
                    else { apple.move(-8,-8); window.draw(apple); }
                }
                else if(level[i][j] == 'v')
                {
                    flagVictory.setPosition((j * 32.f) - 16.f, (i-1) * 32.f);
                    sf::RectangleShape tempFlag;
                    tempFlag.setSize({32, 64}); tempFlag.setPosition((j * 32.f) - 0.f, (i-1) * 32.f);
                    if(player.getGlobalBounds().intersects(tempFlag.getGlobalBounds()) && !player.isVictory)
                    {
                        soundVictory.play();
                        player.isVictory = true;
                    }

                    window.draw(flagVictory);
                }
            }
        }
        for(int i = 0; i < collecteds.size(); ++i)
        {
            window.draw(collecteds[i]);
        }
        for(int i = 0; i < enemies.size(); ++i)
        {
            window.draw(enemies[i]);
        }
        window.draw(player);
        window.display();
    }
    return 0;
}
