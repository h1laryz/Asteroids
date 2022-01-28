#include "Map.h"

Map::Map(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->sprite = createSprite("..\\data\\background.png");
	getSpriteSize(sprite, this->spriteWidth, this->spriteHeight);
	this->countWidth = this->mapWidth / this->spriteWidth + 1; // not always must be +1 (TODO: fix)
	this->countHeight = this->mapHeight / this->spriteHeight + 1;
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
			drawSprite(this->sprite, 0 + i * (this->spriteWidth), 0 + j * (this->spriteHeight));
		}
	}
}

void Map::destroy()
{
	this->~Map();
}
