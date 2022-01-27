#pragma once
#include <utility>
#include "Framework.h"

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
	void getPlayerSpriteSize(int& w, int& h);
	void destroy();
	void move(int dirX, int dirY);
	std::pair<int, int> getPos();
};

