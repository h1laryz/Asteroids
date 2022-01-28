#pragma once
#include "Framework.h"
#include <cstdlib>

class Asteroid
{
private:
	static int count;
	Sprite* sprite;
	int x, y;
	int dirX, dirY;
	bool isSmall;
public:
	Asteroid();
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid(int x, int y);
	void getAsteroidSpriteSize(int& w, int& h);
	void destroy();
	static int getCount();
};

