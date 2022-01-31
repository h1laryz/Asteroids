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
	float x, y;
	float dirXNorm, dirYNorm;
	std::pair<float, float> currVelocity;
	bool isSmall;
	float movementSpeed;

	Asteroid();
	Asteroid(bool isSmall);

	void initPos(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize,
		std::pair<int, int> mapSize, std::pair<int, int> mapPos);
	bool checkTooCloseToPlayer(std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize);
public:
	static bool checkCollisions(Asteroid* first, Asteroid* second);
	Asteroid(std::pair<int, int> pos, bool isSmall);
	Asteroid(std::vector<Asteroid*> asteroids, std::pair<int, int> playerPos, std::pair<int, int> playerSpriteSize, std::pair<int, int> mapSize, std::pair<int, int> mapPos);
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid();
	static void brownianMotion(Asteroid* first, Asteroid* second);
	std::pair<int, int> getAsteroidSpriteSize();
	void flip(int byX, int byY, std::pair<int, int> mapSize);
	static void move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed);
	static int getCount();
	void update();
	std::pair<int, int> getPos();
	std::pair<Asteroid*, Asteroid*> split();
	friend class Map;
};

