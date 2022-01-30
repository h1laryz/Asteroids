#pragma once
#include "Framework.h"
#include <utility>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"

class Map
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int countWidth, countHeight;
	int mapWidth, mapHeight;
	float x, y;
	float velocityX, velocityY;

	int movementSpeed;


	// private methods
	void calculateCountOfSprites(int mapWidth, int mapHeight);
	void flipObjectsOnMap(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, int xBefore, int yBefore, bool vertical, bool horisontal);
public:
	Map(int mapWidth, int mapHeight, int windowWidth, int windowHeight);
	virtual ~Map();
	void drawMap();
	void getMapSpriteSize(int& w, int& h);
	std::pair<int, int> getMapSize();
	void destroy();
	void move(int dirX, int dirY);
	void updatePos(bool left, bool right, bool up, bool down, std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets);
	void flip(std::vector<Asteroid*> asteroids, std::vector<Bullet*> bullets, int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize);
	std::pair<float, float> getPos();
	std::pair<int, int> getCountSprites();
	int getMovementSpeed();

};

