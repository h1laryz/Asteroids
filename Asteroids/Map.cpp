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

	int stop = 1;

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
