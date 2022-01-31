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
	std::vector<Upgrade*> upgrades;
	Upgrade* activatedUpgrade;
	Shield* shield;
	bool isShieldActivated;
	bool isAutoBulletsActivated;
	unsigned int startUpgradeTime;
	unsigned int upgradeSecondsDuration = 7;
	// input
	std::vector<FRKey> inputtedKeys;
	// params
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

	bool checkCollisionsWithCircle(std::pair<float, float> spriteObjectPos, std::pair<int, int> spriteObjectSize,
		std::pair<float, float> shieldPos, float radius);
	void checkShieldCollisions();
	void updateUpgrade();
	bool checkCollisions(std::pair<float, float> firstPos, std::pair<int, int> firstSpriteSize, std::pair<float, float> secondPos, std::pair<int, int> secondSpriteSize);
	void checkUpgradeBeingTaken();
	void drawUpgrades();
	void checkKeys();
	void updateAndDrawBullets();
	void move(FRKey k);
	void checkOutOfBounds();
	void checkPlayerOutOfBounds();
	void checkBulletsOutOfBounds();
	void checkAsteroidsOutOfBounds();
	void spawnAsteroids();
	void checkAsteroidsCollisions();
	void checkAllBulletsCollisions();
	void checkPlayerCollisions();
	void restart();
	void inertia();
public:
	Game();
	Game(int argc, char** argv);
	virtual ~Game();
	
	virtual const char* GetTitle() override;

};

