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
	void updatePos(std::pair<float, float> newPos);
};

