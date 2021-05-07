//
// Created by michal on 05.05.21.
//

#ifndef SIMPLESFMLAPP2_GAME_H
#define SIMPLESFMLAPP2_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Ball.h"

#include <iostream>

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event ev;

    Player player;

    int points;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    std::vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;



    void initVariables();
    void initFonts();
    void initText();
    void initWindow();
public:
    //Constructors and Destructors
    Game();
    ~Game();

    //Accessors
    bool running();
    const bool& getEndGame() const;

    //Modifiers

    //Functions
    void spawnBalls();
    static int randomizeBallType() ;
    void updatePlayer();
    void updateCollision();
    void update();
    void render();
    void pollEvents();

    void updateText();

    void renderText(sf::RenderTarget &target);

};


#endif //SIMPLESFMLAPP2_GAME_H
