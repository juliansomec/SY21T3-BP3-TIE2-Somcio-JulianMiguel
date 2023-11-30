#include "QBlock.h"

QBlock::QBlock()
{
}

QBlock::~QBlock()
{
}

void QBlock::start()
{
	texture = loadTexture("gfx/QBlock.png");

	x = 0;
	y = 0;
	width = 0;
	height = 0;
	isUsed = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void QBlock::update()
{
}

void QBlock::draw()
{
	blit(texture, x, y);
}

int QBlock::getPosX()
{
	return x;
}

int QBlock::getPosY()
{
	return y;
}

int QBlock::getWidth()
{
	return width;
}

int QBlock::getHeight()
{
	return height;
}

bool QBlock::getUsed()
{
	return isUsed;
}

void QBlock::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void QBlock::QBlockUsed()
{
	isUsed = true;
	this->texture = loadTexture("gfx/usedQblock.png");
}

