#include "Crosshair.h"


Crosshair::Crosshair(int windowWidth, int windowHeight)
{
	this->sprite = createSprite("..\\data\\circle.tga");
	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = (float)(windowWidth - this->spriteWidth) / 2;
	this->y = (float)(windowHeight - this->spriteHeight) / 2;
}

Crosshair::~Crosshair()
{
	destroySprite(this->sprite);
}

/// <summary>
/// Updates crosshair pos
/// </summary>
/// <param name="x"> - x new coordinate</param>
/// <param name="y"> - y new coordinate</param>
void Crosshair::update(float x, float y)
{
	// x, y not relative
	this->x = x - (float)this->spriteWidth / 2;
	this->y = y - (float)this->spriteHeight / 2;
}

/// <summary>
/// Draws crosshair's sprite
/// </summary>
void Crosshair::draw()
{
	drawSprite(this->sprite, x, y);
}

std::pair<float, float> Crosshair::getPos() const
{
	return std::pair<float, float>(this->x, this->y);
}

std::pair<int, int> Crosshair::getCrosshairSpriteSize() const
{
	return std::pair<int, int>(this->spriteWidth, this->spriteHeight);
}
