#pragma once
#include "Framework.h"
#include <utility>

class Map
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int countWidth, countHeight;
	int mapWidth, mapHeight;
	int x, y;
	int movementSpeed;


	// private methods
	void calculateCountOfSprites(int mapWidth, int mapHeight);
public:
	Map(int mapWidth, int mapHeight, int windowWidth, int windowHeight);
	virtual ~Map();
	void drawMap();
	void getMapSpriteSize(int& w, int& h);
	std::pair<int, int> getMapSize();
	void destroy();
	void move(int dirX, int dirY);
	void flip(int byX, int byY, std::pair<int, int> playerSpriteSize, std::pair<int, int> windowSize);
	std::pair<int, int> getPos();
	std::pair<int, int> getCountSprites();
	int getMovementSpeed();

};

