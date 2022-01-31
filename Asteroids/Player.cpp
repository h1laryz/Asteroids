#include "Player.h"
#include <iostream>

Player::Player(int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\spaceship.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = static_cast<float>((windowWidth - spriteWidth)) / 2;
	this->y = static_cast<float>((windowHeight - spriteHeight)) / 2;

	this->movementSpeed = 1.0f;
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
	this->velocityX = dirX;
	this->velocityY = dirY;
	this->x = this->x + this->velocityX * this->movementSpeed;
	this->y = this->y + this->velocityY * this->movementSpeed;
}

void Player::updatePos()
{
	if (velocityX < 0)
	{
		this->velocityX -= 0.00001f;
	}
	else if (velocityX > 0)
		this->velocityX += 0.00001f;

	if (velocityY < 0)
		this->velocityY -= 0.00001f;
	else if (velocityY > 0)
		this->velocityY += 0.00001f;

	this->x = this->x + this->velocityX * this->movementSpeed;
	this->y = this->y + this->velocityY * this->movementSpeed;
}



Bullet* Player::shoot(std::pair<int, int> crosshairPos)
{
	return new Bullet(std::pair<int,int>(this->x + this->spriteWidth / 2, this->y + this->spriteHeight / 2), crosshairPos, false);
}

std::pair<float, float> Player::getPos()
{
	return std::pair<float, float>(this->x, this->y);
}

std::pair<int, int> Player::getPlayerSpriteSize()
{
	return std::pair<int, int>(spriteWidth, spriteHeight);
}
