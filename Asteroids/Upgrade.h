#pragma once
#include <vector>
#include <utility>
#include "Framework.h"

class Upgrade
{
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;
public:
	static void move(std::vector<Upgrade*> upgrades, int dirX, int dirY, int movementSpeed);
	Upgrade(std::pair<float, float> pos);
	~Upgrade();
	void draw();
	std::pair<float, float> getPos();
	std::pair<int, int> getUpgradeSpriteSize();
	friend class Map;
};

