#include "Asteroid.h"

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
	count++;
}


Asteroid::Asteroid(std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize, 
	std::pair<int, int> mapSize, std::pair<int, int> mapPos) : Asteroid()
{
	this->x = rand() % mapSize.first + mapPos.first;
	this->y = rand() % mapSize.second + mapPos.second;
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

void Asteroid::getAsteroidSpriteSize(int& w, int& h)
{
	getSpriteSize(this->sprite, w, h);
}

void Asteroid::destroy()
{
	this->~Asteroid();
}

int Asteroid::getCount()
{
	return count;
}


