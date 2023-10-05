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
	float fireRate;
	float maxFireRate;

	//private functions

	void initTexture();
	void initSprite();
	void initVariables();


public:
	Player();
	virtual ~Player();

	//Functions
	void update();
	void render(sf::RenderTarget& renderTarget);
	void updateFireRate();
	void move(sf::RenderWindow& window);
	
	bool canAttack();
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getDirection() const;
	const float getRotation() const;
};

