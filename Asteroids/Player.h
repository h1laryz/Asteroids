#pragma once
#include <utility>
#include "Framework.h"
#include "Bullet.h"

class Player
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;
	float velocityX, velocityY;
	float movementSpeed;
public:
	Player(int windowWidth, int windowHeight);
	virtual ~Player();
	void drawPlayer();
	void destroy();
	void move(int dirX, int dirY);
	void updatePos();
	Bullet* shoot(std::pair<int, int> crosshairPos);
	std::pair<float, float> getPos();
	std::pair<int, int> getPlayerSpriteSize();

};

