#include "Goomba.h"

Goomba::~Goomba()
{
}

void Goomba::start()
{
	texture = loadTexture("gfx/goomba.png");

	x = 0;
	y = 0;
	directionX = 1;
	width = 0;
	height = 0;
	speed = 2;
	verticalSpeed = 0;
	isAlive = true;
	gravity = 1;

	isOnGround = false;
	floor = nullptr;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Goomba::update()
{
	//gravity
	verticalSpeed += gravity;
	y += verticalSpeed;

	x += directionX * speed;
	if (floor)
	{
		int groundLevel = floor->getPosY();

		if (y + height >= groundLevel)
		{
			y = groundLevel - height;
			isOnGround = true;
		}
		else
		{
			isOnGround = false;
		}
	}

	if (isOnGround)
	{
		verticalSpeed = 0;
	}
}

void Goomba::draw()
{
	blit(texture, x, y);
}

int Goomba::getPosX()
{
	return x;
}

int Goomba::getPosY()
{
	return y;
}

int Goomba::getWidth()
{
	return width;
}

int Goomba::getHeight()
{
	return height;
}

void Goomba::setPosX(int pos)
{
	x = pos;
}

void Goomba::setPosY(int pos)
{
	y = pos;
}

bool Goomba::getIsAlive()
{
	return false;
}

void Goomba::doDeath()
{
}

void Goomba::setDirection()
{
	directionX *= -1;
	x -= directionX * speed;
}

void Goomba::setFloor(Environment* ground)
{
	floor = ground;
}
