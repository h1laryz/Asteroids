#pragma once
#include <utility>
#include "Framework.h"

class Bullet
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int x, y;
	int finalX, finalY;
	int speed;
public:
	Bullet(std::pair<int, int> playerPos, std::pair<int, int> crosshairPos);
	void update();
	void draw();
	~Bullet();
};

