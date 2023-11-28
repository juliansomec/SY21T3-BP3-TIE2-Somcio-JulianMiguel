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
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 140) + 50;
	currentDirectionChangeTime = 0;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 50;
}

void Enemy::update()
{
	if (!isAlive) return;
	x += dirX * speed;
	y += dirY * speed;

	if (currentDirectionChangeTime > 0) currentDirectionChangeTime--;
	
	if (currentDirectionChangeTime == 0)
	{
		dirX = -dirX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0) currentReloadTime--;
	
	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPosX(), playerTarget->getPosY(), x, y, &dx, &dy);
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 3 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPosX() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

int Enemy::getPosX()
{
	return x;
}

int Enemy::getPosY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}

void Enemy::explodeState()
{
	this->texture = loadTexture("gfx/explosion.png");
	this->speed = 0;
	this->isAlive = false;
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
