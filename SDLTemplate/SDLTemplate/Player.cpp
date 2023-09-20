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

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = mainSpeed;
	reloadTime = 8;
	specReloadTime = 25;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
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

	if (currentReloadTime > 0) currentReloadTime--;
	if (currentSpecReloadTime > 0) currentSpecReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 3 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentSpecReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(x, y, 1, 0, 10);
		Bullet* bullet2 = new Bullet(x, y - 5 + height, 1, 0, 10);
		bullets.push_back(bullet1);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet1);
		getScene()->addGameObject(bullet2);

		currentSpecReloadTime = specReloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPosX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Player::draw()
{
	blit(texture, x, y);
}


