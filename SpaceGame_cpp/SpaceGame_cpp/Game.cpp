#include "Game.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

//private functions
void Game::initVariables()
{
	this->window = nullptr;
	this->windowWidth = 800;
	this->windowHeight = 600;

	this->asteroidSpawnRate = 1.f;
	this->maxScoreTimer = 15.f;
	this->scoreTimer = 0.f;
	this->currentTime = this->asteroidSpawnRate;
	this->gameOver = false;

}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "SpaceShip_Game");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initBullets()
{
	
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Art/Bullet.png");

	this->textures["ASTEROID1"] = new sf::Texture();
	this->textures["ASTEROID1"]->loadFromFile("Art/Asteroid_1.png");
	
	this->textures["ASTEROID2"] = new sf::Texture();
	this->textures["ASTEROID2"]->loadFromFile("Art/Asteroid_2.png");

	this->textures["PLAYER_GUI"] = new sf::Texture();
	this->textures["PLAYER_GUI"]->loadFromFile("Art/Player_UI.png");

	this->textures["HEART"] = new sf::Texture();
	this->textures["HEART"]->loadFromFile("Art/Heart.png");
}

void Game::initGUI()
{
	//Player photo
	this->playerGUI.setTexture(*this->textures["PLAYER_GUI"]);
	this->playerGUI.setPosition(15, 15);
	this->playerGUI.setScale(3, 3);


	//Score
	this->score = 0;
	if(!this->font.loadFromFile("Art/8-BIT.ttf"))
	{
		std::cout << "FONT NOT FOUND" << std::endl;
	}
	this->scoreGUI.setFont(this->font);
	this->scoreGUI.setString("SCORE  0");
	this->scoreGUI.setPosition(70, 20);
	this->scoreGUI.setFillColor(sf::Color::White);
	this->scoreGUI.setScale(0.5, 0.5);

	//player remaining lifes
	this->heart.setTexture(*this->textures["HEART"]);
	this->heart.setPosition(70, 40);
	this->heart.setScale(2, 2);
	this->playerLifes.push_back(this->heart);
	
	//Game over gui
	this->gameOverGUI.setFont(this->font);
	this->gameOverGUI.setString("GAME OVER");
	this->gameOverGUI.setOrigin(this->gameOverGUI.getGlobalBounds().left + this->gameOverGUI.getGlobalBounds().width / 2.f,
		this->gameOverGUI.getGlobalBounds().top + this->gameOverGUI.getGlobalBounds().height / 2.f);
	this->gameOverGUI.setPosition(this->windowWidth / 2.f, this->windowHeight / 2.f);
	this->gameOverGUI.setFillColor(sf::Color::Red);

	//Game over score
	this->gameOverScoreGUI.setFont(this->font);

	this->gameOverScoreGUI.setOrigin(this->gameOverScoreGUI.getGlobalBounds().left + this->gameOverScoreGUI.getGlobalBounds().width / 2.f,
		this->gameOverScoreGUI.getGlobalBounds().top + this->gameOverScoreGUI.getGlobalBounds().height / 2.f);
	this->gameOverScoreGUI.setPosition(this->windowWidth / 2.f, this->windowHeight / 2.f + 15);
	this->gameOverScoreGUI.setScale(.5f, .5f);
	this->gameOverScoreGUI.setFillColor(sf::Color::Yellow);
}

void Game::updateInput()
{
	//Player shooting 
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) 
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getDirection().x, //direction x
			this->player->getDirection().y, // direction y
			this->player->getPosition().x, //spawn pos x
			this->player->getPosition().y, //spawn pox y
			10.f, //speed
			this->player->getRotation())); //rotation
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//bullet culling 
		
		if(bullet->getBounds().top + bullet->getBounds().height < 0.f ||
			bullet->getBounds().top > this->window->getSize().y ||
			bullet->getBounds().left + bullet->getBounds().width < 0.f ||
			bullet->getBounds().left > this->window->getSize().x)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}

	
}

void Game::updateAsteroids()
{	
	//Generate the random numbers to spawn asteroids
	std::random_device rd;  // Obtain a random seed from the hardware
	std::mt19937 gen(rd()); // Seed the Mersenne Twister generator
	std::uniform_real_distribution<double> distribution(-1.0, 1.0); //random direction
	std::uniform_real_distribution<double> down(.5, 1.0);
	std::uniform_real_distribution<double> top(-1, -0.5);
	std::uniform_real_distribution<double> spawnRandomPosTop(50,750); //random spawn pos


	//Spawning asteroids 
	if(this->currentTime < this->asteroidSpawnRate)
		this->currentTime += 0.005;

	if (this->currentTime >= this->asteroidSpawnRate) 
	{
		this->currentTime = 0.f;
		this->asteroids.push_back(new Asteroid(this->textures["ASTEROID1"], distribution(gen), down(gen), spawnRandomPosTop(gen), -50, 0.5f, 45.f));
		this->asteroids.push_back(new Asteroid(this->textures["ASTEROID1"], distribution(gen), top(gen), spawnRandomPosTop(gen), 600, 0.5f, 90.f));
	}

	//Updating asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		this->asteroids[i]->update();

	}

	
}

void Game::updateCombat()
{
	//Manage asteroids collision with bullets
	for (int i = 0; i < asteroids.size(); i++)
	{
		bool asteroidDeleted = false;

		for (int k = 0; k < bullets.size() && asteroidDeleted == false; k++)
		{
			if (this->bullets[k]->getBounds().intersects(this->asteroids[i]->getAsteroidBounds()))
			{
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				delete this->asteroids[i];
				this->asteroids.erase(this->asteroids.begin() + i);

				asteroidDeleted = true;
				this->score += 100;
			}

		}

	}

	//Manage player collision with asteroids
	for (int i = asteroids.size() - 1; i >= 0; i--)
	{
		if(this->player->getBounds().intersects(asteroids[i]->getAsteroidBounds()))
		{
			this->gameOver = true;
		}
	}

}

void Game::updateScore()
{
	//We add score just by surviving
	if(this->scoreTimer < this->maxScoreTimer)
		this->scoreTimer += 0.1f;
	
	if(this->scoreTimer >= this->maxScoreTimer && !this->gameOver)
	{
		this->scoreTimer = 0.f;
		this->score += 1;
	}
		std::string myScore = std::to_string(this->score);
		this->scoreGUI.setString("SCORE  " + myScore);
}

void Game::renderGUI()
{
	this->window->draw(this->playerGUI);
	this->window->draw(this->scoreGUI);
	
	for (auto _heart : this->playerLifes)
	{
		this->window->draw(_heart);
	}

	if(this->gameOver)
	{
		this->window->draw(this->gameOverGUI);

		std::string myScore = std::to_string(this->score);
		this->gameOverScoreGUI.setString("YOUR SCORE " + myScore);

		this->window->draw(this->gameOverScoreGUI);
	}
}

void Game::restartGame()
{
	//set default values
	this->score = 0;
	this->player->setPosition(400, 300);
	this->gameOver = false;

	//delete all asteroids
	asteroids.clear();
}



//constructor and destructor
Game::Game()
{
	this->initTextures();
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initGUI();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	for (auto &i : this->textures)
	{
		delete i.second;
	}


	for(auto *i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->asteroids)
	{
		delete i;
	}
}

//public functions

void Game::run()
{
	while (this->window->isOpen()) 
	{
		if(!this->gameOver)
		{
			this->update();
		}
		else 
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			{
				this->restartGame();
			}
		}
			
		this->render();
	}
}

void Game::update()
{
	
	sf::Event ev;

	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();
	}
	this->updateInput();

	//Move Player
	this->player->move(*this->window);

	this->updateBullets();

	this->player->update();
	

	std::cout << this->score << std::endl;

	this->updateAsteroids();

	this->updateCombat();
	
	this->updateScore();
}


void Game::render()
{
	//clear the frame
	this->window->clear();

	//here we draw the game
	this->player->render(*this->window);

	//draw bullets
	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* asteroid : this->asteroids)
	{
		asteroid->render(this->window);
	}

	this->renderGUI();
	//display the frame
	this->window->display();
}

