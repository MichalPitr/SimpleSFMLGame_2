//
// Created by michal on 05.05.21.
//

#include "Game.h"

//Constructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 10;
    this->points = 0;
}

void Game::update()
{
    this->pollEvents();
    if (!this->endGame)
    {
        this->spawnBalls();
        this->updateCollision();
        this->updatePlayer();
        this->updateText();
    }
}

void Game::render()
{
    this->window->clear();

    //Render stuff

    this->player.render(this->window);

    for (auto i : this->balls)  // C++ for each equivalent
    {
        i.render(*this->window);
    }

    this->renderText(*this->window);

    if (this->endGame)
    {
        this->window->draw(this->endGameText);
    }

    this->window->display();
}

bool Game::running()
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            default:
                break;
        }
    }
}

void Game::spawnBalls()
{
    if (this->spawnTimer < this->spawnTimerMax)
    {
        this->spawnTimer += 1.f;
    }
    else
    {
        if (this->balls.size() < this->maxBalls)
        {
            this->balls.emplace_back(Ball(*this->window, Game::randomizeBallType())); // more efficient than push back? no copying.
            this->spawnTimer = 0.f;
        }
    }
}

void Game::updateCollision()
{
    //check collision
    for (size_t i = 0; i < this->balls.size(); i++)
    {
        if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
        {
            switch (this->balls[i].getType())
            {
                case BallTypes::DEFAULT:
                    this->points += 1;
                    break;
                case BallTypes::DAMAGING:
                    this->player.takeDamage(1);
                    break;
                case BallTypes::HEALING:
                    this->player.gainHp(1);
                    break;
            }
            this->balls.erase(this->balls.begin()+i);
        }
    }
}

int Game::randomizeBallType()
{
    int type = BallTypes::DEFAULT;
    int randVal = rand() % 100 + 1;
    if (randVal > 60 && randVal <= 80)
    {
        type = BallTypes::DAMAGING;
    }
    else if (randVal > 80)
    {
        type = BallTypes::HEALING;
    }
    return type;
}

void Game::updatePlayer()
{
    this->player.update(this->window);
    if (player.getHp() <= 0)
    {
        this->endGame = true;
    }
}

const bool &Game::getEndGame() const
{
    return this->endGame;
}

void Game::initFonts() {
    if(!this->font.loadFromFile("../media/UbuntuMono-B.ttf"))
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << '\n';
}

void Game::initText() {
    //Start Game Text
    this->guiText.setFont(this->font);
    this->guiText.setCharacterSize(24);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setString("NONE");

    //End Game Text
    this->endGameText.setFont(this->font);
    this->endGameText.setCharacterSize(48);
    this->endGameText.setFillColor(sf::Color::Magenta);
    this->endGameText.setPosition(sf::Vector2f(
            static_cast<float>(this->window->getSize().x)*0.4f,
            static_cast<float>(this->window->getSize().y)*0.4f
            ));
    this->endGameText.setString("GAME OVER");

}

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << '\n'
       <<"Health: " << player.getHp() << '\n';
    this->guiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->guiText);
}
