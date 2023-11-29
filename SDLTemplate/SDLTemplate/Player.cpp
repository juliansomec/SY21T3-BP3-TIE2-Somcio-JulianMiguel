#include "Player.h"
#include "Scene.h"

int mainSpeed = 2;

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = 325;
	y = 1000;
	width = 0;
	height = 0;
	speed = mainSpeed;
	reloadTime = 8;
	specReloadTime = 25;
	currentReloadTime = 0;
	currentPowerUps = 0;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{

		if (bullets[i]->getPosY() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}

	if (!isAlive) return;

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

	if (currentReloadTime > 0) currentReloadTime--;
	if (currentSpecReloadTime > 0) currentSpecReloadTime--;

	int totalBullets = std::max(1, currentPowerUps + 1);

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);

		for (int i = 0; i < totalBullets; ++i)
		{
			float bulletX = x - 3 + width / 2 + i * 15;

			Bullet* bullet = new Bullet(bulletX, y, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}
		currentReloadTime = reloadTime;
	}


	if (app.keyboard[SDL_SCANCODE_G] && currentSpecReloadTime == 0)
	{
		SoundManager::playSound(sound);

		for (int i = 2; i < totalBullets + 3; ++i)
		{
			float bulletX = x - 3 + width / 2 + i * 15;

			Bullet* bullet = new Bullet(bulletX, y, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}
		currentSpecReloadTime = specReloadTime;
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

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::collectPowerUps()
{
	currentPowerUps++;
}


