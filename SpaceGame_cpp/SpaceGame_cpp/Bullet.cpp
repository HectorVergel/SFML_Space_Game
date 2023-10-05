#include "Bullet.h"
#include <iostream>


Bullet::Bullet(sf::Texture* texture, float dirX, float dirY, float posX, float posY, float movementSpeed, float rotation)
{
		this->sprite.setTexture(*texture);
	this->sprite.setPosition(posX, posY);

	this->bulletSpeed = movementSpeed;
	this->dirX = dirX;
	this->dirY = dirY;
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->sprite.setRotation(rotation);

	this->move();

	
}

Bullet::~Bullet()
{

}


void Bullet::render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(this->sprite);
}

void Bullet::update()
{
	this->move();
}

void Bullet::move()
{
	this->sprite.move(this->bulletSpeed * this->direction);
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
