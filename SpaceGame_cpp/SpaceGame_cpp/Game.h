#pragma once

#include "Player.h"
#include "Bullet.h"
#include <vector>
#include <map>

using namespace std;
class Game
{

private:
	sf::RenderWindow* window;

	void initVariables();
	void initWindow();

	std::vector<Bullet*> bullets;
	std::map<std::string, sf::Texture*> textures;

	Player* player;
	void initBullets();
	void initPlayer();
	void initTextures();

	void updateInput();
	void updateBullets();

public:
	Game();
	virtual ~Game();

	void run();
	void update();
	void render();

};

