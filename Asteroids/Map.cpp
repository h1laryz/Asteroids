#include "Map.h"
#include <iostream>

Map::Map(unsigned int &mapWidth, unsigned int &mapHeight, int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\background.png");
	getSpriteSize(sprite, this->spriteWidth, this->spriteHeight);

	this->calculateCountOfSprites(mapWidth, mapHeight);
		
	this->mapWidth = this->spriteWidth * this->countWidth;
	this->mapHeight = this->spriteHeight * this->countHeight;

	mapWidth = this->mapWidth;
	mapHeight = this->mapHeight;

	this->x = (float)(windowWidth - spriteWidth * countWidth) / 2;
	this->y = (float)(windowHeight - spriteHeight * countHeight) / 2;

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
			drawSprite(this->sprite, int(x + i * (this->spriteWidth)), int(y + j * (this->spriteHeight)));
		}
	}
}

float Map::getMovementSpeed()
{
	return this->movementSpeed;
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
	if (dirX != 0)
	{
		this->velocityX = (float)dirX;
		this->x = this->x + this->velocityX * this->movementSpeed;
	}
	if (dirY != 0)
	{
		this->velocityY = (float)dirY;
		this->y = this->y + this->velocityY * this->movementSpeed;
	}
}

void Map::updatePos(bool left, bool right, bool up, bool down, std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades)
{
	float difference = 0.004f;
	if (velocityX > 0 && !left)
	{
		this->velocityX -= difference;
		if (this->velocityX < 0)
			this->velocityX = 0.0f;
	}
	else if (velocityX < 0 && !right)
	{
		this->velocityX += difference;
		if (this->velocityX > 0)
			this->velocityX = 0.0f;
	}

	if (velocityY > 0 && !up)
	{
		this->velocityY -= difference;
		if (this->velocityY < 0)
			this->velocityY = 0.0f;
	}
	else if (velocityY < 0 && !down)
	{
		this->velocityY += difference;
		if (this->velocityY > 0)
			this->velocityY = 0.0f;
	}

	if (!left && !right)
	{
		this->x = this->x + this->velocityX * this->movementSpeed;
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->x = asteroids[i]->x + this->velocityX * this->movementSpeed;
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->x = bullets[i]->x + this->velocityX * this->movementSpeed;
		}
		for (size_t i = 0; i < upgrades.size(); i++)
		{
			upgrades[i]->x = upgrades[i]->x + this->velocityX * this->movementSpeed;
		}
		for (size_t i = 0; i < autoBullets.size(); i++)
		{
			autoBullets[i]->x = autoBullets[i]->x + this->velocityX * this->movementSpeed;
		}
		for (size_t i = 0; i < homingMissiles.size(); i++)
		{
			homingMissiles[i]->x = homingMissiles[i]->x + this->velocityX * this->movementSpeed;
		}
	}
	if (!up && !down)
	{
		this->y = this->y + this->velocityY * this->movementSpeed;
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->y = asteroids[i]->y + this->velocityY * this->movementSpeed;
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->y = bullets[i]->y + this->velocityY * this->movementSpeed;
		}
		for (size_t i = 0; i < upgrades.size(); i++)
		{
			upgrades[i]->y = upgrades[i]->y + this->velocityY * this->movementSpeed;
		}
		for (size_t i = 0; i < autoBullets.size(); i++)
		{
			autoBullets[i]->y = autoBullets[i]->y + this->velocityY * this->movementSpeed;
		}
		for (size_t i = 0; i < homingMissiles.size(); i++)
		{
			homingMissiles[i]->y = homingMissiles[i]->y + this->velocityY * this->movementSpeed;
		}
	}
}

std::pair<float, float> Map::getPos() const
{
	return std::pair<float, float>(this->x, this->y);
}

/// <summary>
/// if player is out of bounds moves map and all objects
/// </summary>
/// <param name="asteroids"></param>
/// <param name="bullets"></param>
/// <param name="autoBullets"></param>
/// <param name="homingMissiles"></param>
/// <param name="upgrades"></param>
/// <param name="xBefore"></param>
/// <param name="yBefore"></param>
/// <param name="vertical"></param>
/// <param name="horisontal"></param>
void Map::flipObjectsOnMap(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades, float xBefore, float yBefore, bool vertical, bool horisontal)
{
	if (vertical)
	{
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->x = this->x - xBefore + asteroids[i]->x;
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->x = this->x - xBefore + bullets[i]->x;
		}

		for (size_t i = 0; i < autoBullets.size(); i++)
		{
			autoBullets[i]->x = this->x - xBefore + autoBullets[i]->x;
		}

		for (size_t i = 0; i < upgrades.size(); i++)
		{
			upgrades[i]->x = this->x - xBefore + upgrades[i]->x;
		}

		for (size_t i = 0; i < homingMissiles.size(); i++)
		{
			homingMissiles[i]->x = this->x - xBefore + homingMissiles[i]->x;
		}
	}
	if (horisontal)
	{
		for (size_t i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->y = this->y - yBefore + asteroids[i]->y;
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->y = this->y - yBefore + bullets[i]->y;
		}

		for (size_t i = 0; i < autoBullets.size(); i++)
		{
			autoBullets[i]->y = this->y - yBefore + autoBullets[i]->y;
		}

		for (size_t i = 0; i < upgrades.size(); i++)
		{
			upgrades[i]->y = this->y - yBefore + upgrades[i]->y;
		}

		for (size_t i = 0; i < homingMissiles.size(); i++)
		{
			homingMissiles[i]->y = this->y - yBefore + homingMissiles[i]->y;
		}
	}
}

std::pair<int, int> Map::getCountSprites() const
{
	return std::pair<int, int>(this->countWidth, this->countHeight);
}

std::pair<int, int> Map::getMapSize() const
{
	return std::pair<int, int>(this->mapWidth, this->mapHeight);
}

void Map::flip(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades, int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize)
{
	float xBefore = this->x;
	float yBefore = this->y;
	// left
	if (byX == -1)
	{
		this->x = windowSize.first - mapWidth - this->x;
		flipObjectsOnMap(asteroids, bullets, autoBullets, homingMissiles, upgrades, xBefore, yBefore, true, false);
	}
	// right
	else if (byX == 1)
	{
		this->x = windowSize.first - mapWidth - this->x - 1;
		flipObjectsOnMap(asteroids, bullets, autoBullets, homingMissiles, upgrades, xBefore, yBefore, true, false);
	}
	// up & down
	if (byY == -1 || byY == 1)
	{
		this->y = windowSize.second - mapHeight - this->y;
		flipObjectsOnMap(asteroids, bullets, autoBullets, homingMissiles, upgrades, xBefore, yBefore, false, true);
	}
}
