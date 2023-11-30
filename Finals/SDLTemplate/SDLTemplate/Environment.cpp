#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::start()
{
	texture = loadTexture("gfx/floor_sprite.png");

	x = 0;
	y = 600;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Environment::update()
{
}

void Environment::draw()
{
	blit(texture, x, y);
}

int Environment::getPosX()
{
	return x;
}

int Environment::getPosY()
{
	return y;
}

int Environment::getWidth()
{
	return width;
}

int Environment::getHeight()
{
	return height;
}
