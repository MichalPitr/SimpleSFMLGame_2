//
// Created by michal on 06.05.21.
//

#include "Player.h"

Player::Player(float x, float y)
{
    this->shape.setPosition(x, y);

    this->initVariables();
    this->initShape();
}

Player::~Player()
{

}

void Player::initVariables()
{

    this->movementSpeed = 8.f;
    this->hpMax = 3;
    this->hp = this->hpMax;
}

void Player::initShape()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

void Player::update(const sf::RenderTarget* target)
{
    //Keyboard input
    this->updateInput();
    //Window bounds collision
    this->updateWindowBounceCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}

void Player::updateInput()
{
    //left or right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->shape.move(-this->movementSpeed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->shape.move(this->movementSpeed, 0.f);
    }
    // up or down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->shape.move(0.f, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->shape.move(0, this->movementSpeed);
    }
}

void Player::updateWindowBounceCollision(const sf::RenderTarget *target)
{
    //left and right.
    if (this->shape.getGlobalBounds().left <= 0.f)
    {
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    }
    else if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= static_cast<float>(target->getSize().x))
    {
        this->shape.setPosition(static_cast<float>(target->getSize().x) - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }
    // top and bottom
    if (this->shape.getGlobalBounds().top <= 0.f)
    {
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
    }
    else if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= static_cast<float>(target->getSize().y))
    {
        this->shape.setPosition(this->shape.getGlobalBounds().left, static_cast<float>(target->getSize().y) - this->shape.getGlobalBounds().height);
    }
}

const sf::RectangleShape &Player::getShape() const
{
    return this->shape;
}

const int &Player::getHp() const
{
    return this->hp;
}

const int &Player::getHpMax() const
{
    return this->hpMax;
}

void Player::gainHp(const int hp)
{
    if (this->hp + hp < this->getHpMax())
    {
        this->hp += hp;
    }
    else {
        this->hp = this->getHpMax();
    }
}

void Player::takeDamage(const int damage)
{
    if (this->hp > 0)
    {
        this->hp -= damage;
    }

    if (this->hp <= 0)
    {
        this->hp = 0;
    }

}


