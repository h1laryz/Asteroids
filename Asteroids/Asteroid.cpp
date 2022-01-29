#include "Asteroid.h"
#include <iostream>

int Asteroid::count = 0;

Asteroid::Asteroid()
{
	this->x = 0;
	this->y = 0;

	this->dirX = rand() % 3 - 1;
	this->dirY = rand() % 3 - 1;

	if (rand() % 2)
	{
		this->sprite = createSprite("..\\data\\big_asteroid.png");
		this->isSmall = false;
	}
	else
	{
		this->sprite = createSprite("..\\data\\small_asteroid.png");
		this->isSmall = true;
	}

	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	count++;
}

void Asteroid::initPos()
{
}

bool Asteroid::checkCollisions(Asteroid* first, Asteroid* second)
{
	return false;
}


Asteroid::Asteroid(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize, 
	std::pair<int, int> mapSize, std::pair<int, int> mapPos) : Asteroid()
{

	bool xCollision, yCollision;
	do
	{
		xCollision = false;
		yCollision = false;

		this->x = rand() % (mapSize.first - this->spriteWidth) + mapPos.first;
		this->y = rand() % (mapSize.second - this->spriteHeight) + mapPos.second;

		for (size_t i = 0; i < asteroids.size(); i++)
		{
			xCollision = false;
			yCollision = false;

			if ((this->x >= asteroids[i]->x && this->x <= asteroids[i]->x + asteroids[i]->spriteWidth)
				|| (this->x + this->spriteWidth >= asteroids[i]->x && this->x + this->spriteWidth <= asteroids[i]->x + asteroids[i]->spriteWidth)
				|| (asteroids[i]->x >= this->x && asteroids[i]->x <= this->x + this->spriteWidth)
				|| (asteroids[i]->x + asteroids[i]->spriteWidth >= this->x && asteroids[i]->x + asteroids[i]->spriteWidth <= this->x + this->spriteWidth))
			{
				xCollision = true;
			}
			
			if ((this->y >= asteroids[i]->y && this->y <= asteroids[i]->y + asteroids[i]->spriteHeight)
				|| (this->y + this->spriteHeight >= asteroids[i]->y && this->y + this->spriteHeight <= asteroids[i]->y + asteroids[i]->spriteHeight)
				|| (asteroids[i]->y >= this->y && asteroids[i]->y <= this->y + this->spriteHeight)
				|| (asteroids[i]->y + asteroids[i]->spriteHeight >= this->y && asteroids[i]->y + asteroids[i]->spriteHeight <= this->y + this->spriteHeight))
			{
				yCollision = true;
			}
			
			if (xCollision && yCollision)
				break;
		}

	} while (xCollision && yCollision);
}

Asteroid::~Asteroid()
{
	destroySprite(this->sprite);
	count--;
}

bool Asteroid::getIsSmall()
{
	return this->isSmall;
}

void Asteroid::move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed)
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->x = asteroids[i]->x + dirX * movementSpeed;
		asteroids[i]->y = asteroids[i]->y + dirY * movementSpeed;
	}
	
}

void Asteroid::drawAsteroid()
{
	drawSprite(this->sprite, this->x, this->y);
}

std::pair<int, int> Asteroid::getAsteroidSpriteSize()
{
	return std::pair<int, int>(spriteWidth, spriteHeight);
}

void Asteroid::destroy()
{
	this->~Asteroid();
}

int Asteroid::getCount()
{
	return count;
}


