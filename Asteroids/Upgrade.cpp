#include "Upgrade.h"

Upgrade::Upgrade()
{
	this->x = 0;
	this->y = 0;

	int random = rand() % 3;
	if (random == 0)
	{
		this->sprite = createSprite("..\\data\\shield.png");
	}
	else if (random == 1)
	{
		this->sprite = createSprite("..\\data\\autobulleticon.png");
	}
	else if (random == 2)
	{

	}

	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);
}

std::string Upgrade::getUpgradeName()
{
	return upgradeName;
}

void Upgrade::move(std::vector<Upgrade*> upgrades, int dirX, int dirY, int movementSpeed)
{
	for (size_t i = 0; i < upgrades.size(); i++)
	{
		upgrades[i]->x = upgrades[i]->x + dirX * movementSpeed;
		upgrades[i]->y = upgrades[i]->y + dirY * movementSpeed;
	}
}

Upgrade::Upgrade(std::pair<float, float> pos)
{
	int random = rand() % 2;
	if (random == 0)
	{
		this->sprite = createSprite("..\\data\\shield.png");
		this->upgradeName = "shield";
	}
	else if (random == 1)
	{
		this->sprite = createSprite("..\\data\\autobulleticon.png");
		this->upgradeName = "autobullets";
	}
	else if (random == 2)
	{

	}

	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = pos.first - this->spriteWidth / 2;
	this->y = pos.second - this->spriteHeight / 2;
}

Upgrade::~Upgrade()
{
	destroySprite(this->sprite);
}

void Upgrade::draw()
{
	if (this->sprite != nullptr)
		drawSprite(this->sprite, this->x, this->y);
}

std::pair<float, float> Upgrade::getPos()
{
	return std::pair<float, float>(this->x, this->y);
}

std::pair<int, int> Upgrade::getUpgradeSpriteSize()
{
	return std::pair<int, int>(this->spriteWidth, this->spriteHeight);
}

void Upgrade::updatePos(std::pair<float, float> newPos)
{
	this->x = newPos.first - this->spriteWidth / 2;
	this->y = newPos.second - this->spriteHeight / 2;
}
