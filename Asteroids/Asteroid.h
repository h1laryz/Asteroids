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
	int x, y;
	int dirX, dirY;
	bool isSmall;

	Asteroid();
public:
	Asteroid(std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize, std::pair<int, int> mapSize, std::pair<int, int> mapPos);
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid();
	void getAsteroidSpriteSize(int& w, int& h);
	void destroy();
	static void move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed);
	static int getCount();
	void flipByMap(std::pair<int, int> mapPos);
	friend class Map;
};

