#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
class Asteroid
{
private:
	float movementSpeed;
	sf::Vector2f direction;

	sf::Sprite sprite;
	//private functions
	void move();

public:
	Asteroid(sf::Texture* texture, float dirX, float dirY, float posX, float posY, float movementSpeed, float rotation);
	virtual ~Asteroid();

	void update();
	void render(sf::RenderTarget* renderTarget);
	
	const sf::FloatRect getAsteroidBounds() const;
};

