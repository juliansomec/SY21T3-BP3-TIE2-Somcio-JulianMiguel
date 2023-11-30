#include "Bricks.h"

Bricks::Bricks()
{
}

Bricks::~Bricks()
{
}

void Bricks::start()
{
	texture = loadTexture("gfx/brick.png");

	x = 0;
	y = 0;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bricks::update()
{
}

void Bricks::draw()
{
	blit(texture, x, y);
}

int Bricks::getPosX()
{
	return x;
}

int Bricks::getPosY()
{
	return y;
}

int Bricks::getWidth()
{
	return width;
}

int Bricks::getHeight()
{
	return height;
}

void Bricks::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
