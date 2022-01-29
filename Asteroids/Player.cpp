#include "Player.h"
#include <iostream>

Player::Player(int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\spaceship.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = (windowWidth - spriteWidth) / 2;
	this->y = (windowHeight - spriteHeight) / 2;
	std::cout << "player pos: " << this->x << " ; " << this->y << std::endl;

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

void Player::destroy()
{
	this->~Player();
}

void Player::move(int dirX, int dirY)
{
	this->x = this->x + dirX * this->movementSpeed;
	this->y = this->y + dirY * this->movementSpeed;
}

Bullet* Player::shoot(std::pair<int, int> crosshairPos)
{
	return new Bullet(std::pair<int,int>(this->x + this->spriteWidth / 2, this->y + this->spriteHeight / 2), crosshairPos);
}

std::pair<int, int> Player::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}

std::pair<int, int> Player::getPlayerSpriteSize()
{
	return std::pair<int, int>(spriteWidth, spriteHeight);
}
