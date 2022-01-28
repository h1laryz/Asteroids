#include "Map.h"

Map::Map(int mapWidth, int mapHeight, int windowWidth, int windowHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->sprite = createSprite("..\\data\\background.png");
	getSpriteSize(sprite, this->spriteWidth, this->spriteHeight);
	this->countWidth = this->mapWidth / this->spriteWidth + 1; // not always must be +1 (TODO: fix)
	this->countHeight = this->mapHeight / this->spriteHeight + 1;

	this->x = (windowWidth - spriteWidth* countWidth) / 2;
	this->y = (windowHeight - spriteHeight* countHeight) / 2;

	this->movementSpeed = 1;

}

Map::~Map()
{
	destroySprite(sprite);
}

void Map::drawMap()
{
	for (size_t i = 0; i < countWidth; i++)
	{
		for (size_t j = 0; j < countHeight; j++)
		{
			drawSprite(this->sprite, x + i * (this->spriteWidth), y + j * (this->spriteHeight));
		}
	}
}

void Map::destroy()
{
	this->~Map();
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

std::pair<int, int> Map::getCountSprites()
{
	return std::pair<int, int>(this->countWidth, this->countHeight);
}

void Map::flip(int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize)
{
	// left
	if (byX == -1)
	{
		this->x = windowSize.first - spriteWidth * countWidth - this->x;
	}
	// right
	else if (byX == 1)
	{
		this->x = windowSize.first - spriteWidth * countWidth - this->x - 1;
	}
	// up & down
	if (byY == -1 || byY == 1)
	{
		this->y = windowSize.second - spriteHeight * countHeight - this->y;
	}
}
