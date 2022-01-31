#pragma once
#include <vector>
#include <utility>
#include "Framework.h"

class Upgrade
{
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;

protected:
	void updateSprite(const char* path);
public:
	static void move(std::vector<Upgrade*> upgrades, int dirX, int dirY, int movementSpeed);
	Upgrade(std::pair<float, float> pos);
	Upgrade(std::pair<float, float> pos, const char* path);
	virtual ~Upgrade();
	virtual void draw();
	virtual void activate(std::pair<float, float> pos);
	std::pair<float, float> getPos();
	std::pair<int, int> getUpgradeSpriteSize();
	void updatePos(std::pair<float, float> newPos);
	friend class Map;
};

