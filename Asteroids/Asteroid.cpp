#include "Asteroid.h"

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
}

Asteroid::~Asteroid()
{
	destroySprite(this->sprite);
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


