#include "Player.h"
#include "Bullet.h"
#include <iostream>



Player::Player()
{
	this->initTexture();
	this->initSprite();

	this->maxSpeed = 7.f;
	this->minSpeed = 1.5f;
	this->moveSpeed = this->minSpeed;

	this->acceleration = 0.15f;
	this->deceleration = 0.0;
}

Player::~Player()
{

}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Art/Player_Ship.png")) {
		std::cout << "Texture not found!";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(2.f, 2.f);
	this->sprite.setOrigin((sf::Vector2f)this->texture.getSize() / 2.f);
	this->sprite.setPosition(50, 50);
}

void Player::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		
		if(this->moveSpeed < 7.f)
			moveSpeed += 0.15f;
	}
	else 
	{
		if (this->moveSpeed > 2.5f)
			moveSpeed -= 0.15f;
	}

	
		
		
	
}

void Player::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(this->sprite);
	
}

void Player::move(sf::RenderWindow& window)
{
	//Rotation of player
	sf::Vector2f currentPosition = this->sprite.getPosition();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	const float PI = 3.14159265;

	float dx = mousePosition.x - currentPosition.x;
	float dy = mousePosition.y - currentPosition.y;

	float rotation = (atan2(-dy, -dx)) * 180 / PI;

	this->sprite.setRotation(rotation + 90);
	
	//Movement of player

	//Normalize direction
	float length = sqrt((dx * dx) + (dy * dy));
	this->normalizedDirectionX = 0.f;
	this->normalizedDirectionY = 0.f;
	if (length != 0) 
	{
		this->normalizedDirectionX = dx / length;
		this->normalizedDirectionY = dy / length;
	}
	//Threshold for moving and not over flip
	if (length > 10.f) 
	{

		//Multipy speed per normalized direction
		this->sprite.move(moveSpeed * this->normalizedDirectionX, moveSpeed * this->normalizedDirectionY);
	}
	
	
	
}
