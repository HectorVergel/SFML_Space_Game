#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Bullet
{
private:
	float bulletSpeed;
	float dirX;
	float dirY;

	sf::Sprite sprite;
	sf::Vector2f direction;

public:
	Bullet(sf::Texture* texture, float dirX, float dirY, float posX, float posY, float movementSpeed, float rotation);
	virtual ~Bullet();

	void render(sf::RenderTarget* renderTarget);
	void update();

	void move();

	const sf::FloatRect getBounds() const;
};

