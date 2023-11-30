#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::start()
{
	texture = loadTexture("gfx/block.png");

	x = 0;
	y = 0;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Block::update()
{
}

void Block::draw()
{
	blit(texture, x, y);
}

int Block::getPosX()
{
	return x;
}

int Block::getPosY()
{
	return y;
}

int Block::getWidth()
{
	return width;
}

int Block::getHeight()
{
	return height;
}

void Block::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
