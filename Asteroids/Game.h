#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Framework.h"
#include "Player.h"
#include "Map.h"
#include "Asteroid.h"

class Game : public Framework 
{
private:
	// game objects
	Player* player;
	Map* map;
	std::vector<Asteroid*> asteroids;
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

	virtual void move(FRKey k);
	void checkOutOfBounce();
public:
	Game();
	Game(int argc, char** argv);
	virtual ~Game();
	virtual void PreInit(int& width, int& height, bool& fullscreen);
	virtual bool Init();
	virtual void Close();
	virtual bool Tick();
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
	virtual void onKeyPressed(FRKey k);
	virtual void onKeyReleased(FRKey k);
	virtual void checkKeys();
	
	virtual const char* GetTitle() override;

};

