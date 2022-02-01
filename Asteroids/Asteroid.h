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
	bool autoBulletTryToHit;

	// private constructors / destructors
	Asteroid();
	Asteroid(bool isSmall);

	// private methods
	void initPos(std::vector<Asteroid*> asteroids, std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize,
		std::pair<int, int> mapSize, std::pair<float, float> mapPos);
public:
	// Constructors / destructors
	Asteroid(std::pair<float, float> pos, bool isSmall);
	Asteroid(std::vector<Asteroid*> asteroids, std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize, std::pair<int, int> mapSize, std::pair<float, float> mapPos);
	~Asteroid();

	// getters
	std::pair<float, float> getPos() const;
	const std::pair<float, float>& getVelocity() const;
	const bool& getAutoBulletTryToHit() const;
	const bool& getIsSmall() const;
	const static int& getCount();
	std::pair<int, int> getAsteroidSpriteSize() const;

	// setters
	void setAutoBulletTryToHit(bool flag);

	// methods
	bool checkTooCloseToPlayer(std::pair<float, float> playerPos, std::pair<int, int> playerSpriteSize);
	void drawAsteroid();
	void update();
	void flip(int byX, int byY, std::pair<int, int> mapSize);
	std::pair<Asteroid*, Asteroid*> split();

	// static
	static bool checkCollisions(Asteroid* first, Asteroid* second);
	static void brownianMotion(Asteroid* first, Asteroid* second);
	static void move(std::vector<Asteroid*> asteroids, int dirX, int dirY, int movementSpeed);

	// friends
	friend class Map;
};

