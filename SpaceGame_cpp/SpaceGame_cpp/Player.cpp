#include "Player.h"
#include "Bullet.h"
#include <iostream>



Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
	
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
	this->sprite.setPosition(400, 300);
}

void Player::initVariables()
{
	this->maxSpeed = 7.f;
	this->minSpeed = 1.5f;
	this->moveSpeed = this->minSpeed;

	this->acceleration = 0.15f;
	this->deceleration = 0.0;
	this->maxFireRate = 10.f;
	this->fireRate = this->maxFireRate;
}

void Player::update()
{
	//Acceleration when right click pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		
		if(this->moveSpeed < 7.f)
			moveSpeed += 0.15f;
	}
	else 
	{
		if (this->moveSpeed > 2.5f)
			moveSpeed -= 0.15f;
	}

	this->updateFireRate();
		
		
	
}

void Player::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(this->sprite);
	
}

void Player::updateFireRate()
{
	if(this->fireRate < this->maxFireRate)
		this->fireRate += 1.f;
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

bool Player::canAttack()
{
	if (this->fireRate >= this->maxFireRate) 
	{
		this->fireRate = 0.f;
		return true;
	}
	else 
	{
		return false;
	}
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Player::getDirection() const
{
	return sf::Vector2f(normalizedDirectionX, normalizedDirectionY);
}

const float Player::getRotation() const
{
	return this->sprite.getRotation();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}


