#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::start()
{
	texture = loadTexture("gfx/Powerup.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::update()
{

}

void PowerUp::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

void PowerUp::getPosX()
{
}

void PowerUp::getPosY()
{
}
