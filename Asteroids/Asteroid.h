#pragma once
#include "Framework.h"
#include <cstdlib>

class Asteroid
{
private:
	static int count;
	Sprite* sprite;
	bool isSmall;
public:
	Asteroid();
	Asteroid(bool isSmall);
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid(int x, int y);
	void getAsteroidSpriteSize(int& w, int& h);
	void destroy();
	static int getCount();
};

