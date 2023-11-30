#include "PowerUps.h"

PowerUps::PowerUps(int posX, int posY, float dirX, float dirY, float speed)
{
	this->x = posX;
	this->y = posY;
	this->directionX = dirX;
	this->directionY = dirY;
	this->speed = speed;
}

PowerUps::~PowerUps()
{
}

void PowerUps::start()
{
	texture = loadTexture("gfx/mushroom.png");

	gravity = 1;
	isOnGround = false;
	verticalSpeed = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUps::update()
{
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

	if (isOnGround) verticalSpeed = 0;
}

void PowerUps::draw()
{
	blit(texture, x, y);
}

int PowerUps::getPosX()
{
	return x;
}

int PowerUps::getPosY()
{
	return y;
}

int PowerUps::getWidth()
{
	return width;
}

int PowerUps::getHeight()
{
	return height;
}

void PowerUps::setPosY(int y)
{
	this->y = y;
}

void PowerUps::setFloor(Environment* ground)
{
	floor = ground;
}
