#include "Asteroid.h"


Asteroid::Asteroid(sf::Texture* texture, float dirX, float dirY, float posX, float posY, float movementSpeed, float rotation)
{
	this->sprite.setTexture(*texture);
	this->sprite.setRotation(rotation);
	this->sprite.setPosition(posX, posY);
	this->sprite.setScale(2.f, 2.f);

	this->movementSpeed = movementSpeed;
	this->direction.x = dirX;
	this->direction.y = dirY;
}

Asteroid::~Asteroid()
{

}

void Asteroid::move()
{
	this->sprite.move(direction * movementSpeed);
	this->sprite.setRotation(this->sprite.getRotation() + 1.f);
}

void Asteroid::update()
{
	this->move();
}

void Asteroid::render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(this->sprite);
}
