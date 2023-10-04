#pragma once

#include "Player.h"
#include "Bullet.h"
#include <vector>

using namespace std;
class Game
{

private:
	sf::RenderWindow* window;

	void initVariables();
	void initWindow();

	
	Player* player;
	void initBullets();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	void run();
	void update();
	void render();

};

