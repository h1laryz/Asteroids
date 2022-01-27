#pragma once
#include "Framework.h"

class Player
{
private:
	Sprite* sprite;

public:
	Player();
	virtual ~Player();
	void drawPlayer(int x, int y);
	void getPlayerSpriteSize(int& w, int& h);
	void destroy();
};

