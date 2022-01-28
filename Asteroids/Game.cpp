#include "Game.h"

Game::Game()
{
	// window
	this->windowWidth = 900; // 320x200 (was default)
	this->windowHeight = 900;
	this->fullscreen = false;

	// map
	this->mapWidth = 600;
	this->mapHeight = 600;

	// properties
	this->numOfBullets = 3;
	this->numOfAsteroids = 10;
	this->abilityProbability = 0.2f;

	// game objects
	this->player = nullptr;
	this->map = nullptr;
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
}

void Game::move(FRKey k)
{
	switch (k)
	{
	case FRKey::RIGHT:
		this->map->move(-1, 0);
		break;

	case FRKey::LEFT:
		this->map->move(1, 0);
		break;

	case FRKey::DOWN:
		this->map->move(0, -1);
		break;

	case FRKey::UP:
		this->map->move(0, 1);
		break;
	}
}

void Game::checkOutOfBounce()
{
	int mapSpriteW, mapSpriteH;
	this->map->getMapSpriteSize(mapSpriteW, mapSpriteH);

	// check left
	if (this->player->getPos().first < this->map->getPos().first)
	{
		this->map->flip(-1, 0, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
	// check right
	else if (this->player->getPos().first + this->player->getPlayerSpriteSize().first > 
		this->map->getCountSprites().first * mapSpriteW + this->map->getPos().first)
	{
		this->map->flip(1, 0, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}

	// check up
	if (this->player->getPos().second < this->map->getPos().second)
	{
		this->map->flip(0, -1, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
	// check down
	else if (this->player->getPos().second + this->player->getPlayerSpriteSize().second
	> this->map->getCountSprites().second * mapSpriteH + this->map->getPos().second)
	{
		this->map->flip(0, 1, player->getPlayerSpriteSize(), std::pair<int, int>(this->windowWidth, this->windowHeight));
	}
}

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width = this->windowWidth;
	height = this->windowHeight;
	fullscreen = this->fullscreen;
}


bool Game::Init() {
	player = new Player(this->windowWidth, this->windowHeight);
	map = new Map(this->mapWidth, this->mapHeight, this->windowWidth, this->windowHeight);
	for (size_t i = 0; i < numOfAsteroids; i++)
	{
		Asteroid* temp = new Asteroid();
		asteroids.push_back(temp);
	}
	return true;
}

// Enters here before closing (its empty but works)
void Game::Close() {
	
}

// Enters here every tick of game running
bool Game::Tick() {
	this->map->drawMap();
	this->spawnAsteroids();
	this->player->drawPlayer();
	this->checkKeys();
	this->checkOutOfBounce();
	return false;
}

void Game::spawnAsteroids()
{
	size_t countOfAsteroids = Asteroid::getCount();

	for (size_t i = countOfAsteroids; i < numOfAsteroids; i++)
	{
		Asteroid* asteroid = new Asteroid;
		asteroids.push_back(asteroid);
	}
	int stop = 1;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {

}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {

}


void Game::onKeyPressed(FRKey k) {
	switch (k)
	{
	case FRKey::RIGHT:
		inputtedKeys.push_back(FRKey::RIGHT);
		break;

	case FRKey::LEFT:
		inputtedKeys.push_back(FRKey::LEFT);
		break;

	case FRKey::DOWN:
		inputtedKeys.push_back(FRKey::DOWN);
		break;

	case FRKey::UP:
		inputtedKeys.push_back(FRKey::UP);
		break;
	}
}

void Game::onKeyReleased(FRKey k) {
	for (size_t i = 0; i < inputtedKeys.size(); i++)
	{
		if (inputtedKeys[i] == k)
		{
			inputtedKeys.erase(inputtedKeys.begin() + i);
		}
	}
	
}

void Game::checkKeys()
{
	for (size_t i = 0; i < inputtedKeys.size(); i++)
	{
		move(inputtedKeys[i]);
	}
}

const char* Game::GetTitle()
{
	return "asteroids";
}