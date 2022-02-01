#pragma once
#include <utility>
#include "Framework.h"

class Crosshair
{
private:
	Sprite* sprite;
	int spriteWidth, spriteHeight;
	float x, y;

public:
	// Constructors / destructors
	Crosshair(int windowWidth, int windowHeight);
	~Crosshair();

	// Methods
	void update(float x, float y);
	void draw();

	// Getters
	std::pair<float, float> getPos() const;
	std::pair<int, int> getCrosshairSpriteSize() const;
};

