#include "Player.h"
#include <iostream>

Player::Player(int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\spaceship.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = (windowWidth - spriteWidth) / 2;
	this->y = (windowHeight - spriteHeight) / 2;
	this->movementSpeed = 1;
}

Player::~Player()
{
	destroySprite(this->sprite);
}

void Player::drawPlayer()
{
	drawSprite(this->sprite, this->x, this->y);
}

void Player::getPlayerSpriteSize(int& w, int& h)
{
	getSpriteSize(this->sprite, w, h);
}

void Player::destroy()
{
	this->~Player();
}

void Player::move(int dirX, int dirY)
{
	this->x = this->x + dirX * this->movementSpeed;
	this->y = this->y + dirY * this->movementSpeed;
}

std::pair<int, int> Player::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}
