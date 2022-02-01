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

void Game::checkOutOfBounds()
{
	this->checkPlayerOutOfBounds();
	this->checkAllBulletsOutOfBounds();
	this->checkAsteroidsOutOfBounds();
}

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

void Game::spawnAsteroids()
{
	size_t countOfAsteroids = Asteroid::getCount();

	for (size_t i = countOfAsteroids; i < numOfAsteroids; i++)
	{
		Asteroid* asteroid = new Asteroid(asteroids, this->player->getPos(), this->player->getPlayerSpriteSize(), std::pair<int, int>(mapWidth, mapHeight), this->map->getPos());
		this->asteroids.push_back(asteroid);
	}

	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		if ((isShieldActivated && !(this->checkCollisionsWithCircle(asteroids[i]->getPos(), asteroids[i]->getAsteroidSpriteSize(), 
			shield->getPos(), shield->getRadius()))) || !isShieldActivated)
		{
			this->asteroids[i]->update();
		}

		this->asteroids[i]->drawAsteroid();
	}
}

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

void Game::checkAllBulletsCollisions()
{
	this->checkBulletsCollisions(this->bullets);
	this->checkBulletsCollisions(this->autoBullets);
	this->checkBulletsCollisions(this->homingMissiles);
}

Asteroid* Game::findAsteroidUnderCrosshair()
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		if (this->checkCollisions(this->crosshair->getPos(), this->crosshair->getCrosshairSpriteSize(), this->asteroids[i]->getPos(), this->asteroids[i]->getAsteroidSpriteSize()))
		{
			return asteroids[i];
		}
	}
	return nullptr;
}

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

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {
	this->crosshair->update(x, y);
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	switch (button)
	{
	case FRMouseButton::LEFT:
		if (isReleased)
		{
			if (bullets.size() == this->numOfBullets)
			{
				bullets[0]->~Bullet();
				bullets.erase(bullets.begin());
			}
			bullets.push_back(this->player->shoot(std::pair<int, int>
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
					homingMissiles.push_back(bullet);
				}
			}
		}
		break;
	}
}

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

void Game::onKeyReleased(FRKey k) {
	for (size_t i = 0; i < this->inputtedKeys.size(); i++)
	{
		if (this->inputtedKeys[i] == k)
		{
			this->inputtedKeys.erase(this->inputtedKeys.begin() + i);
		}
	}
}

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
			if (this->activatedUpgrade->getUpgradeName() == "shield")
			{
				this->isShieldActivated = true;
				this->isAutoBulletsActivated = false;
				this->isHomingMissileActivated = false;
				this->startUpgradeTime = getTickCount();
			}
			else if (this->activatedUpgrade->getUpgradeName() == "autobullets")
			{
				this->isShieldActivated = false;
				this->isAutoBulletsActivated = true;
				this->isHomingMissileActivated = false;
				this->startUpgradeTime = getTickCount();
			}
			else if (this->activatedUpgrade->getUpgradeName() == "homingmissile")
			{
				this->isShieldActivated = false;
				this->isAutoBulletsActivated = false;
				this->isHomingMissileActivated = true;
				this->startUpgradeTime = getTickCount();
			}
			this->upgrades.erase(this->upgrades.begin() + i);
			i = 0;
		}
	}
}

void Game::updateUpgrade()
{
	auto newPos = std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2, this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2);
	if (isShieldActivated)
	{
		if ((getTickCount() - startUpgradeTime) / 1000 < this->upgradeSecondsDuration)
		{
			shield->updatePos(newPos);
			shield->draw();
		}
		else
		{
			isShieldActivated = false;
			this->activatedUpgrade->~Upgrade();
			this->activatedUpgrade = nullptr;
		}
	}
	if (isAutoBulletsActivated)
	{
		unsigned int elapsedTime = getTickCount() - startUpgradeTime;
		if (elapsedTime / 1000 < this->upgradeSecondsDuration)
		{
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				if (asteroids[i]->checkTooCloseToPlayer(this->player->getPos(), this->player->getPlayerSpriteSize()) && !asteroids[i]->getAutoBulletTryToHit())
				{
					Bullet* autoBullet = new Bullet(std::make_pair(this->player->getPos().first + this->player->getPlayerSpriteSize().first / 2, this->player->getPos().second + this->player->getPlayerSpriteSize().second / 2),
						std::make_pair(asteroids[i]->getPos().first + asteroids[i]->getAsteroidSpriteSize().first / 2, asteroids[i]->getPos().second + asteroids[i]->getAsteroidSpriteSize().second / 2), true, nullptr);
					autoBullets.push_back(autoBullet);
					asteroids[i]->setAutoBulletTryToHit(true);
				}
			}
			if (elapsedTime % 2000 == 0)
			{
				for (size_t i = 0; i < asteroids.size(); i++)
				{
					asteroids[i]->setAutoBulletTryToHit(false);
				}
			}
		}
		else
		{
			isAutoBulletsActivated = false;
			this->activatedUpgrade->~Upgrade();
			this->activatedUpgrade = nullptr;
		}
	}
	if (isHomingMissileActivated)
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

void Game::drawUpgrades()
{
	for (size_t i = 0; i < this->upgrades.size(); i++)
	{
		this->upgrades[i]->draw();
	}
}

void Game::checkKeys()
{
	for (size_t i = 0; i < this->inputtedKeys.size(); i++)
	{
		this->move(this->inputtedKeys[i]);
	}
}

void Game::updateAndDrawBullets()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		bullets[i]->draw();
	}
	for (size_t i = 0; i < autoBullets.size(); i++)
	{
		autoBullets[i]->update();
		autoBullets[i]->draw();
	}
	for (size_t i = 0; i < homingMissiles.size(); i++)
	{
		homingMissiles[i]->update();
		homingMissiles[i]->draw();
	}
}

const char* Game::GetTitle()
{
	return "asteroids";
}

void Game::checkAllBulletsOutOfBounds()
{
	for (size_t i = 0; i < autoBullets.size(); i++)
	{
		checkBulletsOutOfBounds(autoBullets[i]);
	}
	for (size_t i = 0; i < bullets.size(); i++)
	{
		checkBulletsOutOfBounds(bullets[i]);
	}
	for (size_t i = 0; i < homingMissiles.size(); i++)
	{
		checkBulletsOutOfBounds(homingMissiles[i]);
	}
}

void Game::checkBulletsCollisions(std::vector<Bullet*>& b)
{
	for (size_t i = 0; i < b.size(); i++)
	{
		std::pair<float, float> bulletPos = b[i]->getPos();
		std::pair<int, int> bpriteSize = b[i]->getBulletSpriteSize();

		for (size_t j = 0; j < asteroids.size(); j++)
		{
			std::pair<int, int> asteroidPos = asteroids[j]->getPos();
			std::pair<int, int> asteroidSpriteSize = asteroids[j]->getAsteroidSpriteSize();

			if (this->checkCollisions(bulletPos, bpriteSize, asteroidPos, asteroidSpriteSize))
			{
				b[i]->~Bullet();
				b.erase(b.begin() + i);

				if (!asteroids[j]->getIsSmall())
				{
					auto newAsteroids = asteroids[j]->split();
					asteroids.push_back(newAsteroids.first);
					asteroids.push_back(newAsteroids.second);
				}
				if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= this->abilityProbability)
				{
					std::pair<float, float> upgradePos;
					upgradePos.first = this->asteroids[j]->getPos().first + this->asteroids[j]->getAsteroidSpriteSize().first / 2;
					upgradePos.second = this->asteroids[j]->getPos().second + this->asteroids[j]->getAsteroidSpriteSize().second / 2;

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
