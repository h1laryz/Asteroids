#include <math.h>
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(std::pair<int, int> playerPos, std::pair<int, int> crosshairPos)
{
	this->sprite = createSprite("..\\data\\bullet.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = playerPos.first;
	this->y = playerPos.second;

	this->aimDir.first = crosshairPos.first - playerPos.first;
	this->aimDir.second = crosshairPos.second - playerPos.second;

	this->aimDirNorm.first = this->aimDir.first / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));
	this->aimDirNorm.second = this->aimDir.second / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));

	this->speed = 1.0f;

	this->currVelocity.first = this->aimDirNorm.first * this->speed;
	this->currVelocity.second = this->aimDirNorm.second * this->speed;

}

void Bullet::move(std::vector<Bullet*> bullets, int dirX, int dirY, int movementSpeed)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->x = bullets[i]->x + dirX * movementSpeed;
		bullets[i]->y = bullets[i]->y + dirY * movementSpeed;
	}
}

void Bullet::update()
{
	this->x += this->currVelocity.first;
	this->y += this->currVelocity.second;
}

void Bullet::draw()
{
	drawSprite(this->sprite, (int)this->x, (int)this->y);
}

Bullet::~Bullet()
{
	destroySprite(this->sprite);
}


