#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float dirX, float dirY, float speed, Side side)
{
	this->x = posX;
	this->y = posY;
	this->directionX = dirX;
	this->directionY = dirY;
	this->speed = speed;
	this->side = side;
}

void Bullet::start()
{
	width = 0;
	height = 0;
	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}
	else
	{
		texture = loadTexture("gfx/alienBullet.png");
	}

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

int Bullet::getPosX()
{
	return x;
}

int Bullet::getPosY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet::getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}
