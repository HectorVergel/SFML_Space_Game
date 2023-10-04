#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Player  
{

private:
	sf::Sprite sprite;
	sf::Texture texture;
	

	float moveSpeed;
	float minSpeed;
	float maxSpeed;

	float acceleration;
	float deceleration;

	float normalizedDirectionX;
	float normalizedDirectionY;

	//private functions

	void initTexture();
	void initSprite();


public:
	Player();
	virtual ~Player();

	//Functions
	void update();
	void render(sf::RenderTarget& renderTarget);

	void move(sf::RenderWindow& window);

};

