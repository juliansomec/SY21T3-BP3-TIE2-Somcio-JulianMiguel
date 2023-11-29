#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::start()
{
	dirY = 1;
	speed = 2;
	texture = loadTexture("gfx/Powerup.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::update()
{
	y += dirY * speed;
}

void PowerUp::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int PowerUp::getPosX()
{
	return x;
}

int PowerUp::getPosY()
{
	return y;
}
