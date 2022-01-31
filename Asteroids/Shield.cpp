#include "Shield.h"

Shield::Shield(std::pair<float, float> pos) : Upgrade(pos, "..\\data\\whiteshield.png")
{

}

void Shield::activate(std::pair<float, float> pos)
{
	this->updateSprite("..\\data\\circleshield.png");
	this->updatePos(pos);
}

Shield::~Shield()
{

}




