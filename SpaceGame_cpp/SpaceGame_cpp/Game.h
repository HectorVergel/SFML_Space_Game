#pragma once

#include "Player.h"
#include "Asteroid.h"
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

	std::map<std::string, sf::Texture*> textures;
	float asteroidSpawnRate;
	float currentTime;

	//GameObjects
	
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> bulletsToDelete;
	Player* player;
	std::vector<Asteroid*> asteroids;

	sf::Sprite playerGUI;
	std::vector<sf::Sprite> playerLifes;
	sf::Sprite heart;
	sf::Text scoreGUI;
	sf::Text gameOverGUI;
	sf::Font font;
	int score;

	float scoreTimer;
	float maxScoreTimer;
	bool gameOver;
	
	//private functions
	

	void initBullets();
	void initPlayer();
	void initTextures();
	void initGUI();

	void updateInput();
	void updateBullets();
	void updateAsteroids();
	void updateCombat();
	void updateScore();

	void renderGUI();

	void restartGame();

public:
	Game();
	virtual ~Game();

	void run();
	void update();
	void render();

};

