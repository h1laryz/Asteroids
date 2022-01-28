#pragma once
#include "Framework.h"

class Map
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int countWidth, countHeight;
	int mapWidth, mapHeight;
public:
	Map(int windowWidth, int windowHeight);
	virtual ~Map();
	void drawMap();
	void getMapSpriteSize(int& w, int& h);
	void destroy();
};

