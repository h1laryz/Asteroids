#include "Map.h"
#include <iostream>

Map::Map(int mapWidth, int mapHeight, int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\background.png");
	getSpriteSize(sprite, this->spriteWidth, this->spriteHeight);

	this->calculateCountOfSprites(mapWidth, mapHeight);
		
	this->mapWidth = this->spriteWidth * this->countWidth;
	this->mapHeight = this->spriteHeight * this->countHeight;

	this->x = (windowWidth - spriteWidth * countWidth) / 2;
	this->y = (windowHeight - spriteHeight * countHeight) / 2;

	this->movementSpeed = 1;

}

Map::~Map()
{
	destroySprite(sprite);
}

void Map::drawMap()
{
	for (int i = 0; i < countWidth; i++)
	{
		for (int j = 0; j < countHeight; j++)
		{
			drawSprite(this->sprite, x + i * (this->spriteWidth), y + j * (this->spriteHeight));
		}
	}
}

void Map::destroy()
{
	this->~Map();
}

int Map::getMovementSpeed()
{
	return movementSpeed;
}

void Map::calculateCountOfSprites(int mapWidth, int mapHeight)
{
	if ((double)mapWidth / this->spriteWidth == mapWidth / this->spriteWidth)
		this->countWidth = mapWidth / this->spriteWidth;
	else
		this->countWidth = mapWidth / this->spriteWidth + 1;

	if ((double)mapHeight / this->spriteHeight == mapHeight / this->spriteHeight)
		this->countHeight = mapHeight / this->spriteHeight;
	else
		this->countHeight = mapHeight / this->spriteHeight + 1;
}

void Map::move(int dirX, int dirY)
{
	this->x = this->x + dirX * this->movementSpeed;
	this->y = this->y + dirY * this->movementSpeed;
}

void Map::getMapSpriteSize(int& w, int& h)
{
	getSpriteSize(this->sprite, w, h);
}

std::pair<int, int> Map::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}

void Map::flipAsteroids(std::vector<Asteroid*> asteroids, int xBefore, int yBefore, bool vertical, bool horisontal)
{
	if (vertical)
	{
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->x = this->x - xBefore + asteroids[i]->x;
		}
	}
	if (horisontal)
	{
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->y = this->y - yBefore + asteroids[i]->y;
		}
	}
}

std::pair<int, int> Map::getCountSprites()
{
	return std::pair<int, int>(this->countWidth, this->countHeight);
}

std::pair<int, int> Map::getMapSize()
{
	return std::pair<int, int>(this->mapWidth, this->mapHeight);
}

void Map::flip(std::vector<Asteroid*> asteroids, int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize)
{
	int xBefore = this->x;
	int yBefore = this->y;
	// left
	if (byX == -1)
	{
		this->x = windowSize.first - spriteWidth * countWidth - this->x;
		flipAsteroids(asteroids, xBefore, yBefore, true, false);
	}
	// right
	else if (byX == 1)
	{
		this->x = windowSize.first - spriteWidth * countWidth - this->x - 1;
		flipAsteroids(asteroids, xBefore, yBefore, true, false);
	}
	// up & down
	if (byY == -1 || byY == 1)
	{
		this->y = windowSize.second - spriteHeight * countHeight - this->y;
		flipAsteroids(asteroids, xBefore, yBefore, false, true);
	}
}
