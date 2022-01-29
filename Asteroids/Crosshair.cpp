#include "Crosshair.h"
#include <iostream>


Crosshair::Crosshair(int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\circle.tga");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	std::cout << spriteWidth << "\n";
	this->x = (windowWidth - this->spriteWidth) / 2;
	this->y = (windowHeight - this->spriteHeight) / 2;

	std::cout << "crosshair x: " << this->x << "\n" << "crosshair y: " << this->y << "\n";
}

Crosshair::~Crosshair()
{
	destroySprite(this->sprite);
}

void Crosshair::update(int x, int y)
{
	// x, y not relative
	this->x = x - this->spriteWidth / 2;
	this->y = y - this->spriteHeight / 2;
}

void Crosshair::draw()
{
	drawSprite(this->sprite, x, y);
}

void Crosshair::destroy()
{
	this->~Crosshair();
}

std::pair<int, int> Crosshair::getPos()
{
	return std::pair<int, int>(this->x, this->y);
}
