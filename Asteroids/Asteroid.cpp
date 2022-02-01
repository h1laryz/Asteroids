#include "Asteroid.h"

int Asteroid::count = 0;

Asteroid::Asteroid()
{
	this->x = 0;
	this->y = 0;

	this->dirXNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + rand() % 2 - 1;
	this->dirYNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + rand() % 2 - 1;

	this->movementSpeed = 0.4f;
	this->autoBulletTryToHit = false;

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

void Asteroid::initPos(std::vector<Asteroid*> asteroids, std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize,
	std::pair<int, int> mapSize, std::pair<float, float> mapPos)
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

void Asteroid::setAutoBulletTryToHit(bool flag)
{
	this->autoBulletTryToHit = flag;
}


bool Asteroid::checkTooCloseToPlayer(std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize)
{
	int range = 0;

	if (this->isSmall) range = 120;
	else range = 170;

	std::pair<float, float> centerOfPlayer;
	std::pair<float, float> centerOfAsteroid;

	centerOfPlayer.first = playerPos.first + (float)playerSpriteSize.first / 2;
	centerOfPlayer.second = playerPos.second + (float)playerSpriteSize.second / 2;

	centerOfAsteroid.first = this->x + spriteWidth / 2;
	centerOfAsteroid.second = this->y + spriteHeight / 2;

	if (fabs(centerOfAsteroid.first - centerOfPlayer.first) <= range && fabs(centerOfAsteroid.second - centerOfPlayer.second) <= range)
		return true;

	return false;
}

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

	this->autoBulletTryToHit = false;

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


Asteroid::Asteroid(std::pair<float, float> pos, bool isSmall)
{
	this->x = pos.first;
	this->y = pos.second;

	this->dirXNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + + rand() % 2 - 1;
	this->dirYNorm = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + + rand() % 2 - 1;

	this->movementSpeed = 0.4f;

	this->autoBulletTryToHit = false;

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

Asteroid::Asteroid(std::vector<Asteroid*> asteroids, std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize,
	std::pair<int, int> mapSize, std::pair<float, float> mapPos) : Asteroid()
{
	this->initPos(asteroids, playerPos, playerSpriteSize, mapSize, mapPos);
	
}

Asteroid::~Asteroid()
{
	destroySprite(this->sprite);
	count--;
}

void Asteroid::move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed)
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->x = asteroids[i]->x + dirX * movementSpeed;
		asteroids[i]->y = asteroids[i]->y + dirY * movementSpeed;
	}
	
}

std::pair<float, float> Asteroid::getPos() const
{
	return std::pair<float, float>(this->x, this->y);
}

const std::pair<float, float>& Asteroid::getVelocity() const
{
	return this->currVelocity;
}

const bool& Asteroid::getAutoBulletTryToHit() const
{
	return this->autoBulletTryToHit;
}

const bool& Asteroid::getIsSmall() const
{
	return this->isSmall;
}

void Asteroid::drawAsteroid()
{
	drawSprite(this->sprite, roundf(this->x), roundf(this->y));
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
	//first->currVelocity = secondVelocity;
	//second->currVelocity = firstVelocity;

	first->currVelocity.first = -first->currVelocity.first;
	first->currVelocity.second = -first->currVelocity.second;

	second->currVelocity.first = -first->currVelocity.first;
	second->currVelocity.second = -second->currVelocity.second;
}


std::pair<int, int> Asteroid::getAsteroidSpriteSize() const
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

const int& Asteroid::getCount()
{
	return count;
}

void Asteroid::update()
{
	this->x += this->currVelocity.first;
	this->y += this->currVelocity.second;
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
		first->x = this->x + (float)first->spriteWidth / 2;
		second->x = this->x - (float)second->spriteWidth / 2 - 2;
	}
	else
	{
		first->x = this->x - (float)first->spriteWidth / 2 - 2;
		second->x = this->x + (float)second->spriteWidth / 2;
	}

	if (rand() % 2)
	{
		first->y = this->y + (float)first->spriteHeight / 2;
		second->y = this->y - (float)second->spriteHeight / 2 - 2;
	}
	else
	{
		first->y = this->y - (float)first->spriteHeight / 2 - 2;
		second->y = this->y + (float)second->spriteHeight / 2;
	}

	return std::pair<Asteroid*, Asteroid*>(first, second);
}


