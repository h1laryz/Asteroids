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

void Shield::updatePos(std::pair<float, float> newPos)
{
	this->x = newPos.first - this->spriteWidth / 2;
	this->y = newPos.second - this->spriteHeight / 2;
}




