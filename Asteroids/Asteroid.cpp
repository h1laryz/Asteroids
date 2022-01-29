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

void Asteroid::initPos(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize,
	std::pair<int, int> mapSize, std::pair<int, int> mapPos)
{
	bool collision = false;
	do
	{
		collision = false;
		do
		{
			this->x = rand() % (mapSize.first - this->spriteWidth) + mapPos.first;
			this->y = rand() % (mapSize.second - this->spriteHeight) + mapPos.second;
		} while (this->checkTooCloseToPlayer(playerPos, playerSpriteSize));
		

		for (size_t i = 0; i < asteroids.size(); i++)
		{
			collision = Asteroid::checkCollisions(this, asteroids[i]);
			if (collision)
				break;
		}

	} while (collision);
}

bool Asteroid::checkTooCloseToPlayer(std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize)
{
	int range = 0;

	if (this->isSmall) range = 70;
	else range = 100;

	std::pair<int, int> centerOfPlayer;
	std::pair<int, int> centerOfAsteroid;

	centerOfPlayer.first = playerPos.first + playerSpriteSize.first / 2;
	centerOfPlayer.second = playerPos.second + playerSpriteSize.second / 2;

	centerOfAsteroid.first = this->x + spriteWidth / 2;
	centerOfAsteroid.second = this->y + spriteHeight / 2;

	if (abs(this->x - centerOfPlayer.first) <= range || abs(this->y - centerOfPlayer.second) <= range)
		return true;

	return false;
}

bool Asteroid::checkCollisions(Asteroid* first, Asteroid* second)
{
	bool xCollision = false;
	bool yCollision = false;

	if ((first->x >= second->x && first->x <= second->x + second->spriteWidth)
		|| (first->x + first->spriteWidth >= second->x && first->x + first->spriteWidth <= second->x + second->spriteWidth)
		|| (second->x >= first->x && second->x <= first->x + first->spriteWidth)
		|| (second->x + second->spriteWidth >= first->x && second->x + second->spriteWidth <= first->x + first->spriteWidth))
	{
		xCollision = true;
	}

	if ((first->y >= second->y && first->y <= second->y + second->spriteHeight)
		|| (first->y + first->spriteHeight >= second->y && first->y + first->spriteHeight <= second->y + second->spriteHeight)
		|| (second->y >= first->y && second->y <= first->y + first->spriteHeight)
		|| (second->y + second->spriteHeight >= first->y && second->y + second->spriteHeight <= first->y + first->spriteHeight))
	{
		yCollision = true;
	}

	return xCollision && yCollision;
}


Asteroid::Asteroid(std::pair<int, int> pos, bool isSmall)
{
	this->x = pos.first;
	this->y = pos.second;

	this->dirX = rand() % 3 - 1;
	this->dirY = rand() % 3 - 1;

	this->isSmall = isSmall;

	if (this->isSmall)
		this->sprite = createSprite("..\\data\\small_asteroid.png");
	else
		this->sprite = createSprite("..\\data\\big_asteroid.png");


	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	count++;
}

Asteroid::Asteroid(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize,
	std::pair<int, int> mapSize, std::pair<int, int> mapPos) : Asteroid()
{
	this->initPos(asteroids, playerPos, playerSpriteSize, mapSize, mapPos);
	
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

std::pair<int, int> Asteroid::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}


