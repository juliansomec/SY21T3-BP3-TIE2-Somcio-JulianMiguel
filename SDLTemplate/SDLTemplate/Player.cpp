#include "Player.h"

int mainSpeed = 2;

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = mainSpeed;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		int tempSpeed = 5;
		speed = tempSpeed;
	}
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = mainSpeed;
	}
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
