#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float dirX, float dirY, float speed)
{
	this->x = posX;
	this->y = posY;
	this->directionX = dirX;
	this->directionY = dirY;
	this->speed = speed;
}

void Bullet::start()
{
	width = 0;
	height = 0;
	texture = loadTexture("gfx/playerBullet.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

float Bullet::getPosX()
{
	return x;
}

float Bullet::getPosY()
{
	return y;
}

float Bullet::getWidth()
{
	return width;
}

float Bullet::getHeight()
{
	return height;
}
