//
// Created by michal on 06.05.21.
//

#ifndef SIMPLESFMLAPP2_PLAYER_H
#define SIMPLESFMLAPP2_PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include<sstream>

class Player
{
private:
    sf::RectangleShape shape;

    float movementSpeed;
    int hpMax;
    int hp;

    void initVariables();
    void initShape();

public:
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    //accessors
    const sf::RectangleShape& getShape() const;
    const int& getHp() const;
    const int& getHpMax() const;


    //Functions
    void takeDamage(const int damage);
    void gainHp(const int hp);

    void updateInput();
    void updateWindowBounceCollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};

#endif //SIMPLESFMLAPP2_PLAYER_H
