#include "Shield.h"


Shield::Shield()
{
	this->x = 0;
	this->y = 0;
	this->sprite = createSprite("..\\data\\circleshield.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);
}

Shield::~Shield()
{
	destroySprite(this->sprite);
}

void Shield::draw()
{
	drawSprite(this->sprite, this->x, this->y);
}

std::pair<float, float> Shield::getPos()
{
	return std::pair<float, float>(this->x, this->y);
}

float Shield::getRadius()
{
	return (float)spriteWidth / 2;
}

void Shield::updatePos(std::pair<float, float> newPos)
{
	this->x = newPos.first - this->spriteWidth / 2;
	this->y = newPos.second - this->spriteHeight / 2;
}

std::pair<int, int> Shield::getShieldSpriteSize()
{
	return std::pair<int, int>(this->spriteWidth, this->spriteHeight);
}




