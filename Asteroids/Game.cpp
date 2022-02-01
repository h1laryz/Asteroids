#include "Game.h"
#include <math.h>

Game::Game()
{
	// window
	this->windowWidth = 900; // 320x200 (was default)
	this->windowHeight = 900;
	this->fullscreen = false;

	// map
	this->mapWidth = 500;
	this->mapHeight = 500;

	// properties
	this->numOfBullets = 3;
	this->numOfAsteroids = 10;
	this->abilityProbability = 0.2f;

	// game objects
	this->player = nullptr;
	this->map = nullptr;
	this->crosshair = nullptr;
	this->activatedUpgrade = nullptr;
	this->shield = nullptr;

	this->isAutoBulletsActivated = false;
	this->isShieldActivated = false;
	this->isHomingMissileActivated = false;

	this->startUpgradeTime = 0;
}

Game::Game(int argc, char** argv) : Game()
{
	for (size_t i = 1; i < argc; i++)
	{
		std::string param = argv[i];
		if (param.size() != 0 && param[0] == '-')
		{
			if (param == "-window")
			{
				std::string windowSize = argv[i + 1];
				this->windowWidth = stoi(windowSize.substr(0, windowSize.find('x')));
				windowSize.erase(0, windowSize.find('x') + 1);
				this->windowHeight = stoi(windowSize.substr(0, windowSize.size()));
			}
			else if (param == "-map")
			{
				std::string mapSize = argv[i + 1];
				this->mapWidth = stoi(mapSize.substr(0, mapSize.find('x')));
				mapSize.erase(0, mapSize.find('x') + 1);
				this->mapHeight = stoi(mapSize.substr(0, mapSize.size()));
			}
			else if (param == "-num_asteroids")
			{
				this->numOfAsteroids = atoi(argv[i + 1]);
			}
			else if (param == "-ability_probability")
			{
				this->abilityProbability = (float)atof(argv[i + 1]);
			}
			else if (param == "-num_ammo")
			{
				this->numOfBullets = atoi(argv[i + 1]);
			}
			i++;
		}
	}
	// check for test in console
	std::cout << "windowWidth " << windowWidth << std::endl <<
		"windowHeight " << windowHeight << std::endl <<
		"mapWidth " << mapWidth << std::endl <<
		"mapHeight " << mapHeight << std::endl <<
		"numOfBullets " << numOfBullets << std::endl <<
		"numOfAsteroids " << numOfAsteroids << std::endl <<
		"abilityProbability " << abilityProbability << std::endl <<
		"fullscreen " << fullscreen << std::endl;
}

Game::~Game()
{
	delete this->player;
	delete this->crosshair;
	delete this->map;
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		delete this->bullets[i];
	}
	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		delete this->asteroids[i];
	}
	for (size_t i = 0; i < this->autoBullets.size(); i++)
	{
		delete this->autoBullets[i];
	}
	for (size_t i = 0; i < this->homingMissiles.size(); i++)
	{
		delete this->homingMissiles[i];
	}
	for (size_t i = 0; i < this->upgrades.size(); i++)
	{
		delete this->upgrades[i];
	}
}

/// <summary>
/// Moves all objects on map
/// </summary>
/// <param name="k"> - depends on key moves in that direction</param>
void Game::move(FRKey k)
{
	switch (k)
	{
	case FRKey::RIGHT:
		this->map->move(-1, 0);
		Asteroid::move(this->asteroids, -1, 0, this->map->getMovementSpeed());
		Bullet::move(this->bullets, this->autoBullets, this->homingMissiles, -1, 0, this->map->getMovementSpeed());
		Upgrade::move(this->upgrades, -1, 0, this->map->getMovementSpeed());
		break;

	case FRKey::LEFT:
		this->map->move(1, 0);
		Asteroid::move(this->asteroids, 1, 0, this->map->getMovementSpeed());
		Bullet::move(this->bullets, this->autoBullets, this->homingMissiles, 1, 0, this->map->getMovementSpeed());
		Upgrade::move(this->upgrades, 1, 0, this->map->getMovementSpeed());
		break;

	case FRKey::DOWN:
		this->map->move(0, -1);
		Asteroid::move(this->asteroids, 0, -1, this->map->getMovementSpeed());
		Bullet::move(this->bullets, this->autoBullets, this->homingMissiles, 0, -1, this->map->getMovementSpeed());
		Upgrade::move(this->upgrades, 0, -1, this->map->getMovementSpeed());
		break;

	case FRKey::UP:
		this->map->move(0, 1);
		Asteroid::move(this->asteroids, 0, 1, this->map->getMovementSpeed());
		Bullet::move(this->bullets, this->autoBullets, this->homingMissiles, 0, 1, this->map->getMovementSpeed());
		Upgrade::move(this->upgrades, 0, 1, this->map->getMovementSpeed());
		break;
	}
}

/// <summary>
/// Calls all out of bounds checks
/// </summary>
void Game::checkOutOfBounds()
{
	this->checkPlayerOutOfBounds();
	this->checkAllBulletsOutOfBounds();
	this->checkAsteroidsOutOfBounds();
}

/// <summary>
/// Checks if there are collisions beetween circle and rectangle object
/// </summary>
/// <param name="spriteObjectPos"> - rectangle object pos</param>
/// <param name="spriteObjectSize"> - rectangle sprite size</param>
/// <param name="circlePos"> - circle position</param>
/// <param name="radius"> - radius of circle</param>
/// <returns>If they collide returns true</returns>
bool Game::checkCollisionsWithCircle(std::pair<float, float> spriteObjectPos, std::pair<int, int> spriteObjectSize, std::pair<float, float> circlePos, float radius)
{
	circlePos.first = (player->getPos().first + player->getPlayerSpriteSize().first / 2);
	circlePos.second = (player->getPos().second + player->getPlayerSpriteSize().second / 2);

	std::pair<float, float> circleDistance;

	spriteObjectPos.first += spriteObjectSize.first / 2;
	spriteObjectPos.second += spriteObjectSize.second / 2;

	circleDistance.first = fabs(circlePos.first - spriteObjectPos.first);
	circleDistance.second = fabs(circlePos.second - spriteObjectPos.second);

	if (circleDistance.first > ((float)spriteObjectSize.first / 2 + radius)) { return false; }
	if (circleDistance.second > ((float)spriteObjectSize.second / 2 + radius)) { return false; }

	if (circleDistance.first <= ((float)spriteObjectSize.first / 2)) { return true; }
	if (circleDistance.second <= ((float)spriteObjectSize.second / 2)) { return true; }

	float cornerDistance_sq = powf((circleDistance.first - spriteObjectSize.first / 2), 2) +
		powf((circleDistance.second - (float)spriteObjectSize.second / 2), 2);

	return (cornerDistance_sq <= (powf(radius, 2)));
}

/// <summary>
/// Moves bullet to another side of map if player is out of bounds
/// </summary>
/// <param name="bullet"></param>
void Game::checkBulletsOutOfBounds(Bullet* bullet) // TODO: pass gameObject* 
{
	// check left
	if (bullet->getPos().first < this->map->getPos().first)
	{
		bullet->flip(-1, 0, std::pair<int, int>(this->mapWidth, this->mapHeight));
	}
	// check right
	else if (bullet->getPos().first + bullet->getBulletSpriteSize().first
	> this->mapWidth + this->map->getPos().first)
	{
		bullet->flip(1, 0, std::pair<int, int>(this->mapWidth, this->mapHeight));
	}

	// check up
	if (bullet->getPos().second < this->map->getPos().second)
	{
		bullet->flip(0, 1, std::pair<int, int>(this->mapWidth, this->mapHeight));
	}
	// check down
	else if (bullet->getPos().second + bullet->getBulletSpriteSize().second
	> this->mapHeight + this->map->getPos().second)
	{
		bullet->flip(0, -1, std::pair<int, int>(this->mapWidth, this->mapHeight));
	}

}

/// <summary>
/// Checks if asteroids are out of bounds
/// </summary>
void Game::checkAsteroidsOutOfBounds()
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		// check left
		if (this->asteroids[i]->getPos().first < this->map->getPos().first)
		{
			this->asteroids[i]->flip(-1, 0, std::pair<int, int>(this->mapWidth, this->mapHeight));
		}
		// check right
		else if (this->asteroids[i]->getPos().first + this->asteroids[i]->getAsteroidSpriteSize().first
		> this->mapWidth + this->map->getPos().first)
		{
			this->asteroids[i]->flip(1, 0, std::pair<int, int>(this->mapWidth, this->mapHeight));
		}

		// check up
		if (this->asteroids[i]->getPos().second < this->map->getPos().second)
		{
			this->asteroids[i]->flip(0, 1, std::pair<int, int>(this->mapWidth, this->mapHeight));
		}
		// check down
		else if (this->asteroids[i]->getPos().second + this->asteroids[i]->getAsteroidSpriteSize().second
		> this->mapHeight + this->map->getPos().second)
		{
			this->asteroids[i]->flip(0, -1, std::pair<int, int>(this->mapWidth, this->mapHeight));
		}
	}
}

/// <summary>
/// Moves player to another side of map if player is out of bounds
/// </summary>
void Game::checkPlayerOutOfBounds()
{
	// check left
	if (this->player->getPos().first < this->map->getPos().first)
	{
		this->map->flip(asteroids, bullets, autoBullets, homingMissiles, upgrades, -1, 0, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
	// check right
	else if (this->player->getPos().first + this->player->getPlayerSpriteSize().first
	> this->mapWidth + this->map->getPos().first)
	{
		this->map->flip(asteroids, bullets, autoBullets, homingMissiles, upgrades, 1, 0, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}

	// check up
	if (this->player->getPos().second < this->map->getPos().second)
	{
		this->map->flip(asteroids, bullets, autoBullets, homingMissiles, upgrades, 0, -1, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
	// check down
	else if (this->player->getPos().second + this->player->getPlayerSpriteSize().second
	> this->mapHeight + this->map->getPos().second)
	{
		this->map->flip(asteroids, bullets, autoBullets, homingMissiles, upgrades, 0, 1, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
}

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width = this->windowWidth;
	height = this->windowHeight;
	fullscreen = this->fullscreen;
}

/// <summary>
/// Inits objects on map
/// </summary>
/// <returns>true - ok, false - failed, application will exit</returns>
bool Game::Init() {
	this->player = new Player(this->windowWidth, this->windowHeight);
	this->map = new Map(this->mapWidth, this->mapHeight, this->windowWidth, this->windowHeight);
	this->crosshair = new Crosshair(this->windowWidth, this->windowHeight);
	this->shield = new Shield;
	this->activatedUpgrade = nullptr;
	return true;
}

// Enters here before closing 
void Game::Close() {
	
}

// Enters here every tick of game running
bool Game::Tick() {
	this->map->drawMap();
	this->spawnAsteroids();
	this->drawUpgrades();
	this->updateUpgrade();
	this->player->drawPlayer();
	this->crosshair->draw();
	this->inertia();
	this->checkKeys();
	this->checkOutOfBounds();
	this->updateAndDrawBullets();
	this->checkAllBulletsCollisions();
	this->checkPlayerCollisions();
	this->checkUpgradeBeingTaken();
	this->checkAsteroidsCollisions();
	return false;
}

/// <summary>
/// Spawn, update, draw asteroids
/// </summary>
void Game::spawnAsteroids()
{
	size_t countOfAsteroids = Asteroid::getCount();

	for (size_t i = countOfAsteroids; i < this->numOfAsteroids; i++)
	{
		Asteroid* asteroid = new Asteroid(this->asteroids, this->player->getPos(), this->player->getPlayerSpriteSize(), std::pair<int, int>(mapWidth, mapHeight), this->map->getPos());
		this->asteroids.push_back(asteroid);
	}

	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		if ((this->isShieldActivated && !(this->checkCollisionsWithCircle(this->asteroids[i]->getPos(), this->asteroids[i]->getAsteroidSpriteSize(),
			this->shield->getPos(), this->shield->getRadius()))) || !this->isShieldActivated)
		{
			this->asteroids[i]->update();
		}
		this->asteroids[i]->drawAsteroid();
	}
}

/// <summary>
/// Check collisions between asteroids
/// </summary>
void Game::checkAsteroidsCollisions()
{
	/*for (size_t i = 0; i < asteroids.size(); i++)
	{
		for (size_t j = 1; j < asteroids.size(); j++)
		{
			if (i != j)
			{
				if (Asteroid::checkCollisions(asteroids[i], asteroids[j])) 
				{
					Asteroid::brownianMotion(asteroids[i], asteroids[j]);
				}
			}
		}
	}*/
}

/// <summary>
/// Checks all bullets collisions
/// </summary>
void Game::checkAllBulletsCollisions()
{
	this->checkBulletsCollisions(this->bullets);
	this->checkBulletsCollisions(this->autoBullets);
	this->checkBulletsCollisions(this->homingMissiles);
}

/// <summary>
/// Finds asteroid under crosshair
/// </summary>
/// <returns>asteroid under crosshair</returns>
Asteroid* Game::findAsteroidUnderCrosshair()
{
	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		if (this->checkCollisions(this->crosshair->getPos(), this->crosshair->getCrosshairSpriteSize(), this->asteroids[i]->getPos(), this->asteroids[i]->getAsteroidSpriteSize()))
		{
			return this->asteroids[i];
		}
	}
	return nullptr;
}

/// <summary>
/// Checks collisions between 2 objects
/// </summary>
/// <param name="firstPos"> - position of first object</param>
/// <param name="firstSpriteSize"> - sprite size of first object</param>
/// <param name="secondPos"> - position of second object</param>
/// <param name="secondSpriteSize"> - sprite size of second object</param>
/// <returns>true if 2 objects collides</returns>
bool Game::checkCollisions(std::pair<float, float> firstPos, std::pair<int, int> firstSpriteSize, std::pair<float, float> secondPos, std::pair<int, int> secondSpriteSize)
{
	bool xCollision = false;
	bool yCollision = false;

	if ((firstPos.first >= secondPos.first && firstPos.first <= secondPos.first + secondSpriteSize.first)
		|| (firstPos.first + firstSpriteSize.first >= secondPos.first && firstPos.first + firstSpriteSize.first <= secondPos.first + secondSpriteSize.first)
		|| (secondPos.first >= firstPos.first && secondPos.first <= firstPos.first + firstSpriteSize.first)
		|| (secondPos.first + secondSpriteSize.first >= firstPos.first && secondPos.first + secondSpriteSize.first <= firstPos.first + firstSpriteSize.first))
	{
		xCollision = true;
	}

	if ((firstPos.second >= secondPos.second && firstPos.second <= secondPos.second + secondSpriteSize.second)
		|| (firstPos.second + firstSpriteSize.second >= secondPos.second && firstPos.second + firstSpriteSize.second <= secondPos.second + secondSpriteSize.second)
		|| (secondPos.second >= firstPos.second && secondPos.second <= firstPos.second + firstSpriteSize.second)
		|| (secondPos.second + secondSpriteSize.second >= firstPos.second && secondPos.second + secondSpriteSize.second <= firstPos.second + firstSpriteSize.second))
	{
		yCollision = true;
	}

	return xCollision && yCollision;
}

/// <summary>
/// Checks players collisions with asteroids
/// </summary>
void Game::checkPlayerCollisions()
{
	auto playerPos = this->player->getPos();
	auto playerSpriteSize = this->player->getPlayerSpriteSize();

	for (size_t j = 0; j < this->asteroids.size(); j++)
	{
		auto asteroidPos = this->asteroids[j]->getPos();
		auto asteroidSpriteSize = this->asteroids[j]->getAsteroidSpriteSize();

		if (this->checkCollisions(playerPos, playerSpriteSize, asteroidPos, asteroidSpriteSize))
			this->restart();
	}
}

/// <summary>
/// Restarts game
/// </summary>
void Game::restart()
{
	delete this->shield;
	delete this->activatedUpgrade;
	this->isAutoBulletsActivated = false;
	this->isShieldActivated = false;
	this->isHomingMissileActivated = false;
	delete this->player;
	delete this->crosshair;
	delete this->map;
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		delete this->bullets[i];
	}
	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		delete this->asteroids[i];
	}
	for (size_t i = 0; i < this->autoBullets.size(); i++)
	{
		delete this->autoBullets[i];
	}
	for (size_t i = 0; i < this->homingMissiles.size(); i++)
	{
		delete this->homingMissiles[i];
	}
	for (size_t i = 0; i < this->upgrades.size(); i++)
	{
		delete this->upgrades[i];
	}
	this->bullets.clear();
	this->asteroids.clear();
	this->autoBullets.clear();
	this->upgrades.clear();
	this->homingMissiles.clear();
	this->Init();
}

/// <summary>
/// Inertia of moving of player
/// </summary>
void Game::inertia()
{
	bool left = false,
		right = false,
		up = false, 
		down = false;
	for (size_t i = 0; i < this->inputtedKeys.size(); i++)
	{
		switch (inputtedKeys[i])
		{
		case FRKey::RIGHT:
			right = true;
			break;

		case FRKey::LEFT:
			left = true;
			break;

		case FRKey::DOWN:
			down = true;
			break;

		case FRKey::UP:
			up = true;
			break;
		}
	}
	this->map->updatePos(left, right, up, down, asteroids, bullets, autoBullets, homingMissiles, upgrades);
}

// On mouse moving enters here
void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {
	this->crosshair->update((int)x, (int)y);
}

// On mouse button click enters here
void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	switch (button)
	{
	case FRMouseButton::LEFT:
		if (isReleased)
		{
			if (this->bullets.size() == this->numOfBullets)
			{
				this->bullets[0]->~Bullet();
				this->bullets.erase(this->bullets.begin());
			}
			this->bullets.push_back(this->player->shoot(std::pair<int, int>
				(this->crosshair->getPos().first + this->crosshair->getCrosshairSpriteSize().first / 2,
					this->crosshair->getPos().second + this->crosshair->getCrosshairSpriteSize().second / 2)));
		}
		break;

	case FRMouseButton::RIGHT:
		if (isReleased)
		{
			unsigned int elapsedTime = getTickCount() - startUpgradeTime;
			if (this->isHomingMissileActivated && elapsedTime / 1000 < this->upgradeSecondsDuration)
			{
				Asteroid* ast = findAsteroidUnderCrosshair();
				if (ast != nullptr)
				{
					Bullet* bullet = new Bullet(std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2,
						this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2),
						std::make_pair(ast->getPos().first + ast->getAsteroidSpriteSize().first / 2, ast->getPos().second + ast->getAsteroidSpriteSize().second / 2), false, ast);
					this->homingMissiles.push_back(bullet);
				}
			}
		}
		break;
	}
}

// On key pressed enters here
void Game::onKeyPressed(FRKey k) {
	switch (k)
	{
	case FRKey::RIGHT:
		this->inputtedKeys.push_back(FRKey::RIGHT);
		break;

	case FRKey::LEFT:
		this->inputtedKeys.push_back(FRKey::LEFT);
		break;

	case FRKey::DOWN:
		this->inputtedKeys.push_back(FRKey::DOWN);
		break;

	case FRKey::UP:
		this->inputtedKeys.push_back(FRKey::UP);
		break;
	}
}

// On key released enters here
void Game::onKeyReleased(FRKey k) {
	for (size_t i = 0; i < this->inputtedKeys.size(); i++)
	{
		if (this->inputtedKeys[i] == k)
		{
			this->inputtedKeys.erase(this->inputtedKeys.begin() + i);
		}
	}
}

// Activates upgrade that was taken
void Game::checkUpgradeBeingTaken()
{
	auto playerPos = this->player->getPos();
	auto playerSpriteSize = this->player->getPlayerSpriteSize();

	for (size_t i = 0; i < upgrades.size(); i++)
	{
		auto upgradePos = upgrades[i]->getPos();
		auto upgradeSpriteSize = upgrades[i]->getUpgradeSpriteSize();
		if (checkCollisions(playerPos, playerSpriteSize, upgradePos, upgradeSpriteSize))
		{
			if (this->activatedUpgrade != nullptr)
				this->activatedUpgrade->~Upgrade();

			this->activatedUpgrade = upgrades[i];
			this->isShieldActivated = false;
			this->isAutoBulletsActivated = false;
			this->isHomingMissileActivated = false;

			auto newPos = std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2, this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2);
			this->startUpgradeTime = getTickCount();

			if (this->activatedUpgrade->getUpgradeName() == "shield")
			{
				this->isShieldActivated = true;
			}
			else if (this->activatedUpgrade->getUpgradeName() == "autobullets")
			{
				this->isAutoBulletsActivated = true;
			}
			else if (this->activatedUpgrade->getUpgradeName() == "homingmissile")
			{
				this->isHomingMissileActivated = true;
			}
			this->upgrades.erase(this->upgrades.begin() + i);
			i = 0;
		}
	}
}

// Updates upgrades
void Game::updateUpgrade()
{
	auto newPos = std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2, this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2);
	if (this->isShieldActivated)
	{
		if ((getTickCount() - this->startUpgradeTime) / 1000 < this->upgradeSecondsDuration)
		{
			this->shield->updatePos(newPos);
			this->shield->draw();
		}
		else
		{
			this->isShieldActivated = false;
			this->activatedUpgrade->~Upgrade();
			this->activatedUpgrade = nullptr;
		}
	}
	else if (this->isAutoBulletsActivated)
	{
		unsigned int elapsedTime = getTickCount() - this->startUpgradeTime;
		if (elapsedTime / 1000 < this->upgradeSecondsDuration)
		{
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				if (asteroids[i]->checkTooCloseToPlayer(this->player->getPos(), this->player->getPlayerSpriteSize()) && !asteroids[i]->getAutoBulletTryToHit())
				{
					Bullet* autoBullet = new Bullet(std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2, this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2),
						std::make_pair(asteroids[i]->getPos().first + asteroids[i]->getAsteroidSpriteSize().first / 2, asteroids[i]->getPos().second + asteroids[i]->getAsteroidSpriteSize().second / 2), true, nullptr);
					this->autoBullets.push_back(autoBullet);
					this->asteroids[i]->setAutoBulletTryToHit(true);
				}
			}
			if (elapsedTime % 2000 == 0)
			{
				for (size_t i = 0; i < asteroids.size(); i++)
				{
					this->asteroids[i]->setAutoBulletTryToHit(false);
				}
			}
		}
		else
		{
			this->isAutoBulletsActivated = false;
			this->activatedUpgrade->~Upgrade();
			this->activatedUpgrade = nullptr;
		}
	}
	else if (this->isHomingMissileActivated)
	{
		unsigned int elapsedTime = getTickCount() - startUpgradeTime;
		if (elapsedTime / 1000 >= this->upgradeSecondsDuration)
		{
			for (size_t i = 0; i < homingMissiles.size(); i++)
			{
				this->homingMissiles[i]->~Bullet();
			}
			this->homingMissiles.clear();
			this->isHomingMissileActivated = false;
			this->activatedUpgrade->~Upgrade();
			this->activatedUpgrade = nullptr;
		}
	}
}

// Draws upgrades
void Game::drawUpgrades()
{
	for (size_t i = 0; i < this->upgrades.size(); i++)
	{
		this->upgrades[i]->draw();
	}
}

// Checks what keys are pressed
void Game::checkKeys()
{
	for (size_t i = 0; i < this->inputtedKeys.size(); i++)
	{
		this->move(this->inputtedKeys[i]);
	}
}

// Updates and draws bullets
void Game::updateAndDrawBullets()
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i]->update();
		this->bullets[i]->draw();
	}
	for (size_t i = 0; i < this->autoBullets.size(); i++)
	{
		this->autoBullets[i]->update();
		this->autoBullets[i]->draw();
	}
	for (size_t i = 0; i < this->homingMissiles.size(); i++)
	{
		this->homingMissiles[i]->update();
		this->homingMissiles[i]->draw();
	}
}

const char* Game::GetTitle()
{
	return "asteroids";
}

// Checks all bullets for being out of bounds
void Game::checkAllBulletsOutOfBounds()
{
	for (size_t i = 0; i < this->autoBullets.size(); i++)
	{
		this->checkBulletsOutOfBounds(this->autoBullets[i]);
	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->checkBulletsOutOfBounds(this->bullets[i]);
	}
	for (size_t i = 0; i < this->homingMissiles.size(); i++)
	{
		this->checkBulletsOutOfBounds(this->homingMissiles[i]);
	}
}

// Checks bullets for being out of bounds
void Game::checkBulletsCollisions(std::vector<Bullet*>& b)
{
	for (size_t i = 0; i < b.size(); i++)
	{
		auto bulletPos = b[i]->getPos();
		auto bpriteSize = b[i]->getBulletSpriteSize();

		for (size_t j = 0; j < this->asteroids.size(); j++)
		{
			auto asteroidPos = this->asteroids[j]->getPos();
			auto asteroidSpriteSize = this->asteroids[j]->getAsteroidSpriteSize();

			if (this->checkCollisions(bulletPos, bpriteSize, asteroidPos, asteroidSpriteSize))
			{
				b[i]->~Bullet();
				b.erase(b.begin() + i);

				if (!this->asteroids[j]->getIsSmall())
				{
					auto newAsteroids = this->asteroids[j]->split();
					this->asteroids.push_back(newAsteroids.first);
					this->asteroids.push_back(newAsteroids.second);
				}
				if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= this->abilityProbability)
				{
					std::pair<float, float> upgradePos;
					upgradePos.first = this->asteroids[j]->getPos().first + (float)this->asteroids[j]->getAsteroidSpriteSize().first / 2;
					upgradePos.second = this->asteroids[j]->getPos().second + (float)this->asteroids[j]->getAsteroidSpriteSize().second / 2;

					Upgrade* upgrade = new Upgrade(upgradePos);
					this->upgrades.push_back(upgrade);
				}
				this->asteroids[j]->~Asteroid();
				this->asteroids.erase(this->asteroids.begin() + j);
				i = 0;
				break;
			}
		}
	}
}
