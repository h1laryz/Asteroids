#pragma once
#include <vector>
#include <utility>
#include <string>
#include "Framework.h"

class Upgrade
{
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;
	std::string upgradeName;

public:
	std::string getUpgradeName();
	static void move(std::vector<Upgrade*> upgrades, int dirX, int dirY, float movementSpeed);
	Upgrade(std::pair<float, float> pos);
	~Upgrade();
	void draw();
	std::pair<float, float> getPos();
	std::pair<int, int> getUpgradeSpriteSize();
	void updatePos(std::pair<float, float> newPos);
	friend class Map;
};

