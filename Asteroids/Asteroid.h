#pragma once
#include "Framework.h"
#include <cstdlib>
#include <utility>
#include <vector>

class Asteroid
{
private:
	static int count;
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int x, y;
	int dirX, dirY;
	bool isSmall;

	Asteroid();
	void initPos(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize,
		std::pair<int, int> mapSize, std::pair<int, int> mapPos);
	bool checkTooCloseToPlayer(std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize);
	static bool checkCollisions(Asteroid* first, Asteroid* second);
public:
	Asteroid(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize, std::pair<int, int> mapSize, std::pair<int, int> mapPos);
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid();
	std::pair<int, int> getAsteroidSpriteSize();
	void destroy();
	static void move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed);
	static int getCount();
	friend class Map;
};

