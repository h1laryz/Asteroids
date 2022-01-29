#pragma once
#include <utility>
#include "Framework.h"

class Bullet
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;
	std::pair<float, float> aimDir;
	std::pair<float, float> aimDirNorm;
	std::pair<float, float> currVelocity;
	float speed;
public:
	Bullet(std::pair<int, int> playerPos, std::pair<int, int> crosshairPos);
	void update();
	void draw();
	~Bullet();
};

