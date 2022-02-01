#pragma once
#include "Framework.h"
#include <utility>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"
#include "Upgrade.h"

class Map
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int countWidth, countHeight;
	int mapWidth, mapHeight;
	float x, y;
	float velocityX, velocityY;

	float movementSpeed;

	// private methods
	void calculateCountOfSprites(int mapWidth, int mapHeight);
	void flipObjectsOnMap(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades, float xBefore, float yBefore, bool vertical, bool horisontal);

public:
	// Constructors / destructors
	Map(unsigned int &mapWidth, unsigned int &mapHeight, int windowWidth, int windowHeight);
	~Map();

	// Methods
	void drawMap();
	void move(int dirX, int dirY);
	void flip(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades, int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize);
	void updatePos(bool left, bool right, bool up, bool down, std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, std::vector<Upgrade*> upgrades);

	// Getters
	std::pair<int, int> getMapSize() const;
	std::pair<float, float> getPos() const;
	std::pair<int, int> getCountSprites() const;
	float getMovementSpeed();
};

