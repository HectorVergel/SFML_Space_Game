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



//constructor and destructor
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
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
	//Move Player
	this->player->move(*this->window);

	this->player->update();

	
}


void Game::render()
{
	//clear the frame
	this->window->clear();

	//here we draw the game
	this->player->render(*this->window);

	//display the frame
	this->window->display();
}

