//
// Created by michal on 06.05.21.
//

#ifndef SIMPLESFMLAPP2_BALL_H
#define SIMPLESFMLAPP2_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NUMTYPES};

class Ball
{
private:
    sf::CircleShape shape;
    int type;

    void initShape(const sf::RenderWindow& window);
public:
    Ball(const sf::RenderWindow& window, int type);
    virtual ~Ball();

    //Accessor
    const sf::CircleShape& getShape() const;
    const int& getType() const;

    //functions
    void update();
    void render(sf::RenderTarget& target);
};


#endif //SIMPLESFMLAPP2_BALL_H
