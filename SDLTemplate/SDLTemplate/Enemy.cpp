#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = loadTexture("gfx/enemy.png");

	dirX = -1;
	dirY = 1;
	x = 1000;
	y = 300;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 180;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += dirX * speed;
	y += dirY * speed;

	if (currentDirectionChangeTime > 0) currentDirectionChangeTime--;
	
	if (currentDirectionChangeTime == 0)
	{
		dirY = -dirY;
		currentDirectionChangeTime = directionChangeTime;
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}
