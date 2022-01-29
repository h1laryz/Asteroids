#pragma once
#include <utility>
#include <vector>
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
	static void move(std::vector<Bullet*> bullets, int dirX, int dirY, int movementSpeed);
	void update();
	void draw();
	~Bullet();
	std::pair<float, float> getPos();
	std::pair<int, int> getBulletSpriteSize();
	void flip(int byX, int byY, std::pair<int, int> mapSize);
	friend class Map;
};

