#pragma once
#include <utility>
#include "Framework.h"

class Crosshair
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int x, y;

public:
	Crosshair(int windowWidth, int windowHeight);
	~Crosshair();
	void update(int x, int y);
	void draw();
	void destroy();
	void move();
	std::pair<int, int> getPos();
	std::pair<int, int> getCrosshairSpriteSize();
};

