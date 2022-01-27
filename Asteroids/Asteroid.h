#pragma once
#include "Framework.h"
#include <cstdlib>

class Asteroid
{
private:
	Sprite* sprite;
	bool isSmall;
public:
	Asteroid();
	virtual ~Asteroid();
	bool getIsSmall();
	void drawAsteroid(int x, int y);
	void getAsteroidSpriteSize(int& w, int& h);
	void destroy();
};

