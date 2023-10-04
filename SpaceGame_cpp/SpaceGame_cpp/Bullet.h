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

	sf::Texture texture;

	void initSprite();
	void initTexture();
	
public:
	sf::Sprite sprite;
	Bullet(float dirX, float dirY);
	virtual ~Bullet();

	void render(sf::RenderTarget& renderTarget);
	void update();

	void move();
};

