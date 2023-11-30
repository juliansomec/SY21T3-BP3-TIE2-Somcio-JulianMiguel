#include "Player.h"

Player::~Player()
{
}

void Player::start()
{
	texture = loadTexture("gfx/mario.png");

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 5;
	verticalSpeed = 0;
	isAlive = true;
	gravity = 1;

	isOnGround = false;
	isTall = false;
	floor = nullptr;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/MarioJump.ogg");
	sound->volume = 10;
}

void Player::update()
{
	//gravity
	verticalSpeed += gravity;
	y += verticalSpeed;

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

	if (app.keyboard[SDL_SCANCODE_D]) x += speed;
	if (app.keyboard[SDL_SCANCODE_A]) x -= speed;

	if (app.keyboard[SDL_SCANCODE_SPACE] && isOnGround)
	{
		SoundManager::playSound(sound);
		verticalSpeed -= speed * 3;
		isOnGround = false;
	}
	else
	{
		isOnGround = false;
	}
}

void Player::draw()
{
	if (!isAlive) return;
	blit(texture, x, y);
}

int Player::getPosX()
{
	return x;
}

int Player::getPosY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

void Player::setPosX(int pos)
{
	x = pos;
}

void Player::setPosY(int pos)
{
	y = pos;
}

bool Player::getIsAlive()
{
	return isAlive;
}

bool Player::getIsTall()
{
	return isTall;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::collectPowerUp()
{
	isTall = true;
	texture = loadTexture("gfx/tallmario.png");
	height = (height * 2) - 10;
}

void Player::setFloor(Environment* ground)
{
	floor = ground;
}
