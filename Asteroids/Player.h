#pragma once
#include <utility>
#include "Framework.h"
#include "Bullet.h"

class Player
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	int x, y;
	int movementSpeed;
public:
	Player(int windowWidth, int windowHeight);
	virtual ~Player();
	void drawPlayer();
	void destroy();
	void move(int dirX, int dirY);
	Bullet* shoot(std::pair<int, int> crosshairPos);
	std::pair<int, int> getPos();
	std::pair<int, int> getPlayerSpriteSize();

};

