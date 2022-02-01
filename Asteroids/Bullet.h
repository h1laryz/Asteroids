#pragma once
#include <utility>
#include <vector>
#include "Framework.h"
#include "Asteroid.h"

class Bullet
{
private:
	static int count;
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;
	std::pair<float, float> aimDir;
	std::pair<float, float> aimDirNorm;
	std::pair<float, float> currVelocity;
	float speed;

	Asteroid* asteroid;
public:
	// static
	static int getCount();
	static void move(std::vector<Bullet*> bullets, std::vector<Bullet*> autoBullets, std::vector<Bullet*> homingMissiles, int dirX, int dirY, float movementSpeed);

	// Constructors / destructors
	Bullet(std::pair<float, float> playerPos, std::pair<int, int> crosshairPos, bool autoBullet, Asteroid* aim);
	~Bullet();

	// Getters
	std::pair<float, float> getPos() const;
	std::pair<int, int> getBulletSpriteSize() const;

	// Setters


	// Methods
	void update();
	void draw();
	void flip(int byX, int byY, std::pair<int, int> mapSize);

	// Friends
	friend class Map;
};

