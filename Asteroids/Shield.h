#pragma once
#include <utility>
#include <vector>
#include "Framework.h"

class Shield 
{
	Sprite* sprite;
	float x, y;
	int spriteWidth, spriteHeight;
public:
	Shield();
	~Shield();
	void draw();
	std::pair<float, float> getPos();
	float getRadius();
	void updatePos(std::pair<float, float> newPos);
	std::pair<int, int> getShieldSpriteSize();
};

