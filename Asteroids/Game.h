#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Framework.h"
#include "Player.h"
#include "Map.h"
#include "Asteroid.h"
#include "Crosshair.h"
#include "Bullet.h"

class Game : public Framework 
{
private:
	// game objects
	Player* player;
	Map* map;
	Crosshair* crosshair;
	std::vector<Asteroid*> asteroids;
	std::vector<Bullet*> bullets;
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


	void checkKeys();
	void updateAndDrawBullets();
	void move(FRKey k);
	void checkOutOfBounds();
	void checkPlayerOutOfBounds();
	void checkBulletsOutOfBounds();
	void checkAsteroidsOutOfBounds();
	void spawnAsteroids();
	void checkAllBulletsCollisions();
	void checkPlayerCollisions();
	void restart();
	bool checkBulletHit(std::pair<float, float> bulletPos, std::pair<int, int> bulletSpriteSize, std::pair<int, int> asteroidPos, std::pair<int, int> asteroidSpriteSize);

public:
	Game();
	Game(int argc, char** argv);
	virtual ~Game();
	
	virtual const char* GetTitle() override;

};

