#include "Bullet.h"

Bullet::Bullet(std::pair<int, int> playerPos, std::pair<int, int> crosshairPos)
{
	this->sprite = createSprite("..\\data\\bullet.png");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = playerPos.first;
	this->y = playerPos.second;

	this->finalX = crosshairPos.first;
	this->finalY = crosshairPos.second;

	this->speed = 1;
}

void Bullet::update()
{
	if (this->finalX > this->x) 
		this->x = this->x + 1 * this->speed;
	else if (this->finalX < this->x)
		this->x = this->x - 1 * this->speed;

	if (this->finalY > this->y)
		this->y = this->y + 1 * this->speed;
	else if (this->finalY < this->y)
		this->y = this->y - 1 * this->speed;
}

void Bullet::draw()
{
	drawSprite(this->sprite, this->x, this->y);
}

Bullet::~Bullet()
{
	destroySprite(this->sprite);
}


