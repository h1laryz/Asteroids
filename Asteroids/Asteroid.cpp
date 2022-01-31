#include "Asteroid.h"

int Asteroid::count = 0;

Asteroid::Asteroid()
{
	this->x = 0;
	this->y = 0;

	this->dirXNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + rand() % 2 - 1;
	this->dirYNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + rand() % 2 - 1;

	this->movementSpeed = 0.4f;

	this->currVelocity.first = this->dirXNorm * this->movementSpeed;
	this->currVelocity.second = this->dirYNorm * this->movementSpeed;

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

	if (this->isSmall) range = 120;
	else range = 170;

	std::pair<float, float> centerOfPlayer;
	std::pair<float, float> centerOfAsteroid;

	centerOfPlayer.first = playerPos.first + playerSpriteSize.first / 2;
	centerOfPlayer.second = playerPos.second + playerSpriteSize.second / 2;

	centerOfAsteroid.first = this->x + spriteWidth / 2;
	centerOfAsteroid.second = this->y + spriteHeight / 2;

	if (fabs(centerOfAsteroid.first - centerOfPlayer.first) <= range && fabs(centerOfAsteroid.second - centerOfPlayer.second) <= range)
		return true;

	return false;
}

//bool Asteroid::checkCollisions(Asteroid* first, Asteroid* second)
//{
//	bool xCollision = false;
//	bool yCollision = false;
//
//	if ((first->x >= second->x && first->x <= second->x + second->spriteWidth)
//		|| (first->x + first->spriteWidth >= second->x && first->x + first->spriteWidth <= second->x + second->spriteWidth)
//		|| (second->x >= first->x && second->x <= first->x + first->spriteWidth)
//		|| (second->x + second->spriteWidth >= first->x && second->x + second->spriteWidth <= first->x + first->spriteWidth))
//	{
//		xCollision = true;
//	}
//
//	if ((first->y >= second->y && first->y <= second->y + second->spriteHeight)
//		|| (first->y + first->spriteHeight >= second->y && first->y + first->spriteHeight <= second->y + second->spriteHeight)
//		|| (second->y >= first->y && second->y <= first->y + first->spriteHeight)
//		|| (second->y + second->spriteHeight >= first->y && second->y + second->spriteHeight <= first->y + first->spriteHeight))
//	{
//		yCollision = true;
//	}
//
//	return xCollision && yCollision;
//}

bool Asteroid::checkCollisions(Asteroid* first, Asteroid* second)
{
	bool xCollision = false;
	bool yCollision = false;

	if (first->x >= second->x && first->x <= second->x + second->spriteWidth
		|| second->x >= first->x && second->x <= first->x + first->spriteWidth)
	{
		xCollision = true;
	}

	if (first->y >= second->y && first->y <= second->y + second->spriteHeight
		|| second->y >= first->y && second->y <= first->y + first->spriteHeight)
	{
		yCollision = true;
	}

	return xCollision && yCollision;
}

Asteroid::Asteroid(bool isSmall)
{
	this->x = 0;
	this->y = 0;

	this->dirXNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + +rand() % 2 - 1;
	this->dirYNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + +rand() % 2 - 1;

	this->movementSpeed = 0.4f;

	this->currVelocity.first = this->dirXNorm * this->movementSpeed;
	this->currVelocity.second = this->dirYNorm * this->movementSpeed;

	this->isSmall = isSmall;

	if (this->isSmall)
		this->sprite = createSprite("..\\data\\small_asteroid.png");
	else
		this->sprite = createSprite("..\\data\\big_asteroid.png");


	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	count++;
}


Asteroid::Asteroid(std::pair<int, int> pos, bool isSmall)
{
	this->x = pos.first;
	this->y = pos.second;

	this->dirXNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + + rand() % 2 - 1;
	this->dirYNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + + rand() % 2 - 1;

	this->movementSpeed = 0.4f;

	this->currVelocity.first = this->dirXNorm * this->movementSpeed;
	this->currVelocity.second = this->dirYNorm * this->movementSpeed;

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

void Asteroid::brownianMotion(Asteroid* first, Asteroid* second)
{
	std::pair<float, float> firstVelocity = first->currVelocity;
	std::pair<float, float> secondVelocity = second->currVelocity;

	//if (firstVelocity.first > secondVelocity.first)
	//{
	//	secondVelocity.first = second->currVelocity.first + (fabs(first->currVelocity.first) - fabs(second->currVelocity.first));
	//	//firstVelocity.first = first->currVelocity.first - fabs(second->currVelocity.first);
	//}
	//else if (firstVelocity.first < secondVelocity.first)
	//{
	//	firstVelocity.first = first->currVelocity.first + (fabs(first->currVelocity.first) - fabs(second->currVelocity.first));
	//	//secondVelocity.first = second->currVelocity.first - fabs(first->currVelocity.first);
	//}

	//if (firstVelocity.second > secondVelocity.second)
	//{
	//	//firstVelocity.second = first->currVelocity.second - fabs(second->currVelocity.second);
	//	secondVelocity.second = second->currVelocity.second + (fabs(first->currVelocity.second) - fabs(second->currVelocity.second));
	//}
	//else if (firstVelocity.second < secondVelocity.second)
	//{
	//	//secondVelocity.second = second->currVelocity.second - fabs(first->currVelocity.second);
	//	firstVelocity.second = second->currVelocity.second + (fabs(first->currVelocity.second) - fabs(second->currVelocity.second));
	//}
	first->currVelocity = secondVelocity;
	second->currVelocity = firstVelocity;
}


std::pair<int, int> Asteroid::getAsteroidSpriteSize()
{
	return std::pair<int, int>(spriteWidth, spriteHeight);
}

void Asteroid::flip(int byX, int byY, std::pair<int, int> mapSize)
{
	// flip by left
	if (byX == -1)
	{
		this->x = this->x + mapSize.first - this->spriteWidth;
	}
	// flip by right
	else if (byX == 1)
	{
		this->x = this->x - mapSize.first + this->spriteWidth;
	}
	
	// flip by up
	if (byY == 1)
	{
		this->y = this->y + mapSize.second - this->spriteHeight;
	}
	// flip by down
	else if (byY == -1)
	{
		this->y = this->y - mapSize.second + this->spriteHeight;
	}
}

int Asteroid::getCount()
{
	return count;
}

void Asteroid::update()
{
	this->x += this->currVelocity.first;
	this->y += this->currVelocity.second;
}

std::pair<int, int> Asteroid::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}

std::pair<Asteroid*, Asteroid*> Asteroid::split()
{
	if (this->isSmall)
		return std::pair<Asteroid*, Asteroid*>(nullptr, nullptr);

	std::pair<int, int> firstNewPos, secondNewPos;
	Asteroid* first = new Asteroid(true);
	Asteroid* second = new Asteroid(true);

	// TODO: fix (may spawn behind map and teleport from another side)

	if (rand() % 2)
	{
		first->x = this->x + first->spriteWidth / 2;
		second->x = this->x - second->spriteWidth / 2 - 2;
	}
	else
	{
		first->x = this->x - first->spriteWidth / 2 - 2;
		second->x = this->x + second->spriteWidth / 2;
	}

	if (rand() % 2)
	{
		first->y = this->y + first->spriteHeight / 2;
		second->y = this->y - second->spriteHeight / 2 - 2;
	}
	else
	{
		first->y = this->y - first->spriteHeight / 2 - 2;
		second->y = this->y + second->spriteHeight / 2;
	}

	return std::pair<Asteroid*, Asteroid*>(first, second);
}


