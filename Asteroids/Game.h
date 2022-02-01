#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Framework.h"
#include "Player.h"
#include "Map.h"
#include "Asteroid.h"
#include "Crosshair.h"
#include "Bullet.h"
#include "Upgrade.h"
#include "Shield.h"

class Game : public Framework 
{
private:
	// game objects
	Player* player;
	Map* map;
	Crosshair* crosshair;
	std::vector<Asteroid*> asteroids;
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> autoBullets;
	std::vector<Bullet*> homingMissiles;
	std::vector<Upgrade*> upgrades;
	Upgrade* activatedUpgrade;
	Shield* shield;

	// is upgrade activated
	bool isShieldActivated;
	bool isAutoBulletsActivated;
	bool isHomingMissileActivated;

	// for calculating time of upgrade
	unsigned int startUpgradeTime;
	unsigned int upgradeSecondsDuration = 7;

	// input
	std::vector<FRKey> inputtedKeys;

	// params of game
	unsigned int windowWidth, 
		windowHeight, 
		mapWidth, 
		mapHeight, 
		numOfBullets, 
		numOfAsteroids;
	float abilityProbability;
	bool fullscreen;

	// Framework override
	void PreInit(int& width, int& height, bool& fullscreen) override;
	bool Init() override;
	void Close() override;
	bool Tick() override;
	void onMouseMove(int x, int y, int xrelative, int yrelative) override;
	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;
	void onKeyPressed(FRKey k) override;
	void onKeyReleased(FRKey k) override;

	// private methods
	Asteroid* findAsteroidUnderCrosshair();
	void move(FRKey k);
	void restart();
	void inertia();
	void checkKeys();

	// check collisions
	void checkAsteroidsCollisions();
	void checkAllBulletsCollisions();
	bool checkCollisionsWithCircle(std::pair<float, float> spriteObjectPos, std::pair<int, int> spriteObjectSize,
		std::pair<float, float> shieldPos, float radius);
	bool checkCollisions(std::pair<float, float> firstPos, std::pair<int, int> firstSpriteSize, std::pair<float, float> secondPos, std::pair<int, int> secondSpriteSize);
	void checkBulletsCollisions(std::vector<Bullet*>& b);
	void checkPlayerCollisions();

	// check out of bounds
	void checkOutOfBounds();
	void checkAllBulletsOutOfBounds();
	void checkPlayerOutOfBounds();
	void checkBulletsOutOfBounds(Bullet* bullet);
	void checkAsteroidsOutOfBounds();

	// Update / draw
	void updateUpgrade();
	void checkUpgradeBeingTaken();
	void drawUpgrades();
	void spawnAsteroids();
	void updateAndDrawBullets();
public:
	// Constructors / destructors
	Game();
	Game(int argc, char** argv);
	~Game();

	// Getters
	const char* GetTitle() override;
};

