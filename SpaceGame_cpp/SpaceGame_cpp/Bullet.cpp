#include "Bullet.h"
#include <iostream>


Bullet::Bullet(float dirX, float dirY)
{
	this->initTexture();
	this->initSprite();

	this->bulletSpeed = 5.f;
	this->dirX = dirX;
	this->dirY = dirY;

	this->move();

}

Bullet::~Bullet()
{

}

void Bullet::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(2.f, 2.f);
	this->sprite.setOrigin((sf::Vector2f)this->texture.getSize() / 2.f);
}

void Bullet::initTexture()
{
	if (!this->texture.loadFromFile("Art/Bullet.png"))
		std::cout << "BULLET.CPP/TEXTURE NOT FOUND" << std::endl;

}

void Bullet::render(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(this->sprite);
}

void Bullet::update()
{
	
}

void Bullet::move()
{
	this->sprite.move(this->dirX * this->bulletSpeed, this->dirY * this->bulletSpeed);
}
