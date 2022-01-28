#include "Asteroid.h"

int Asteroid::count = 0;

Asteroid::Asteroid()
{
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

Asteroid::Asteroid(bool isSmall)
{
	if (isSmall)
	{
		this->sprite = createSprite("..\\data\\small_asteroid.png");
		this->isSmall = true;
	}
	else
	{
		this->sprite = createSprite("..\\data\\big_asteroid.png");
		this->isSmall = false;
	}
	count++;
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

void Asteroid::drawAsteroid(int x, int y)
{
	drawSprite(this->sprite, x, y);
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


