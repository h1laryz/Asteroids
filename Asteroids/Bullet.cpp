#include <math.h>
#include "Bullet.h"

int Bullet::count = 0;

int Bullet::getCount()
{
	return Bullet::count;
}

Bullet::Bullet(std::pair<float, float> playerPos, std::pair<int, int> crosshairPos, bool autoBullet, Asteroid* aim)
{
	this->asteroid = nullptr;
	if (autoBullet) this->sprite = createSprite("..\\data\\autobullet.png"); 
	else if (aim != nullptr)
	{
		this->sprite = createSprite("..\\data\\homingmissile.png");
		this->asteroid = aim;
	}
	else 
		this->sprite = createSprite("..\\data\\bullet.png");

	getSpriteSize(this->sprite, this->spriteWidth, this->spriteHeight);

	this->x = playerPos.first;
	this->y = playerPos.second;

	this->aimDir.first = crosshairPos.first - playerPos.first;
	this->aimDir.second = crosshairPos.second - playerPos.second;

	this->aimDirNorm.first = this->aimDir.first / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));
	this->aimDirNorm.second = this->aimDir.second / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));

	this->speed = 1.0f;

	this->currVelocity.first = this->aimDirNorm.first * this->speed;
	this->currVelocity.second = this->aimDirNorm.second * this->speed;

	count++;
}

/// <summary>
/// Moves all bullets
/// </summary>
/// <param name="bullets"> - all bullets</param>
/// <param name="autoBullets"> - all autobullets</param>
/// <param name="homingMissiles"> - all homing missiles</param>
/// <param name="dirX"> - x direction</param>
/// <param name="dirY"> - y direction</param>
/// <param name="movementSpeed"> - movement speed</param>
void Bullet::move(std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, int dirX, int dirY, float movementSpeed)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->x = bullets[i]->x + dirX * movementSpeed;
		bullets[i]->y = bullets[i]->y + dirY * movementSpeed;
	}
	for (size_t i = 0; i < autoBullets.size(); i++)
	{
		autoBullets[i]->x = autoBullets[i]->x + dirX * movementSpeed;
		autoBullets[i]->y = autoBullets[i]->y + dirY * movementSpeed;
	}
}

/// <summary>
/// Updates bullets position / velocity
/// </summary>
void Bullet::update()
{
	if (this->asteroid != nullptr)
	{
		this->aimDir.first = this->asteroid->getPos().first + (float)this->asteroid->getAsteroidSpriteSize().first / 2 - this->x;
		this->aimDir.second = this->asteroid->getPos().second + (float)this->asteroid->getAsteroidSpriteSize().second / 2 - this->y;

		this->aimDirNorm.first = this->aimDir.first / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));
		this->aimDirNorm.second = this->aimDir.second / sqrt(pow(this->aimDir.first, 2) + pow(this->aimDir.second, 2));

		this->currVelocity.first = this->aimDirNorm.first * this->speed;
		this->currVelocity.second = this->aimDirNorm.second * this->speed;
	}
	this->x += this->currVelocity.first;
	this->y += this->currVelocity.second;
}

/// <summary>
/// Draws bullet's sprite
/// </summary>
void Bullet::draw()
{
	drawSprite(this->sprite, (int)this->x, (int)this->y);
}


Bullet::~Bullet()
{
	destroySprite(this->sprite);
	count--;
}

std::pair<float, float> Bullet::getPos() const
{
	return std::pair<float, float>(this->x, this->y);
}

std::pair<int, int> Bullet::getBulletSpriteSize() const
{
	return std::pair<int, int>(this->spriteWidth, this->spriteHeight);
}

/// <summary>
/// Moves bullet to another side of map
/// </summary>
/// <param name="byX"> (-1) - flip by left, 1 - flip by right</param>
/// <param name="byY"> (-1) - flip by down, 1 - flip by up</param>
/// <param name="mapSize"> - map's sprite size</param>
void Bullet::flip(int byX, int byY, std::pair<int, int> mapSize)
{
	// flip by left
	if (byX == -1)
	{
		this->x += mapSize.first;
	}
	// flip by right
	else if (byX == 1)
	{
		this->x -= mapSize.first;
	}

	// flip by up
	if (byY == 1)
	{
		this->y += mapSize.second;
	}
	// flip by down
	else if (byY == -1)
	{
		this->y -= mapSize.second;
	}
}


