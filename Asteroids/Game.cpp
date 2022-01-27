#include "Game.h"

Game::Game()
{
	// window
	this->windowWidth = 640; // 320x200 (was default)
	this->windowHeight = 560;
	this->fullscreen = false;

	// map
	this->mapWidth = 700;
	this->mapHeight = 700;

	// properties
	this->numOfBullets = 3;
	this->numOfAsteroids = 10;
	this->abilityProbability = 0.2f;

	// game objects
	this->player = nullptr;
	
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

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width = this->windowWidth;
	height = this->windowHeight;
	fullscreen = this->fullscreen;
}


bool Game::Init() {
	player = new Player();
	return true;
}

// Enters here before closing (its empty but works)
void Game::Close() {

}

// Enters here every tick of game running
bool Game::Tick() {
	drawTestBackground();
	this->player->drawPlayer(0, 0);
	return false;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {

}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {

}

void Game::onKeyPressed(FRKey k) {

}

void Game::onKeyReleased(FRKey k) {

}

const char* Game::GetTitle()
{
	return "asteroids";
}