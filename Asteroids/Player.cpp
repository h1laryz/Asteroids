#include "Player.h"

Player::Player()
{
	this->sprite = createSprite("..\\data\\spaceship.png");
}

Player::~Player()
{
	delete this->sprite;
}

void Player::drawPlayer(int x, int y)
{
	drawSprite(this->sprite, x, y);
}

void Player::getPlayerSpriteSize(int& w, int& h)
{
	getSpriteSize(this->sprite, w, h);
}

void Player::destroy()
{
	this->~Player();
}
