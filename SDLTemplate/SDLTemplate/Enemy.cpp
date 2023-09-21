#include "Enemy.h"
#include "Scene.h"

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

	if (currentReloadTime > 0) currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPosX(), playerTarget->getPosY(), x, y, &dx, &dy);
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 3 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}
