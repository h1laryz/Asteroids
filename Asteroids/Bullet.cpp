#include <math.h>
#include "Bullet.h"

int Bullet::count = 0;

int Bullet::getCount()
{
	return Bullet::count;
}

Bullet::Bullet(std::pair<int, int> playerPos, std::pair<int, int> crosshairPos, bool autoBullet)
{
	if (!autoBullet) this->sprite = createSprite("..\\data\\bullet.png");
	else this->sprite = createSprite("..\\data\\autobullet.png");

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

	count++;
}


void Bullet::move(std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, int dirX, int dirY, int movementSpeed)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->x = bullets[i]->x + dirX * movementSpeed;
		bullets[i]->y = bullets[i]->y + dirY * movementSpeed;
	}
	for (size_t i = 0; i < autoBullets.size(); i++)
	{
		autoBullets[i]->x = autoBullets[i]->x + dirX * movementSpeed;
		autoBullets[i]->y = autoBullets[i]->y + dirY * movementSpeed;
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
	count--;
}

std::pair<float, float> Bullet::getPos()
{
	return std::pair<float, float>(this->x, this->y);
}

std::pair<int, int> Bullet::getBulletSpriteSize()
{
	return std::pair<int, int>(this->spriteWidth, this->spriteHeight);
}

void Bullet::flip(int byX, int byY, std::pair<int, int> mapSize)
{
	// flip by left
	if (byX == -1)
	{
		this->x += mapSize.first;
	}
	// flip by right
	else if (byX == 1)
	{
		this->x -= mapSize.first;
	}

	// flip by up
	if (byY == 1)
	{
		this->y += mapSize.second;
	}
	// flip by down
	else if (byY == -1)
	{
		this->y -= mapSize.second;
	}
}


