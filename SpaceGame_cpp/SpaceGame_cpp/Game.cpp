#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

//private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SpaceShip_Game");
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
		if(bullet->getBounds().top + bullet->getBounds().height < 0.f )
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}



//constructor and destructor
Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initTextures();
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
}

//public functions

void Game::run()
{
	while (this->window->isOpen()) 
	{
		this->update();
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

	//display the frame
	this->window->display();
}

