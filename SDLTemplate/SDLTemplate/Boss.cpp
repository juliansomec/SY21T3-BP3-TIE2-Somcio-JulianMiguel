#include "Boss.h"
#include "Scene.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
	texture = loadTexture("gfx/boss.png");

	x = 0;
	y = -300;
	width = 768;
	height = 300;
	speed = 2;
	reloadTime = 50;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 140) + 50;
	currentDirectionChangeTime = 0;
	isAlive = true;
    health = 3000;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 50;
}

void Boss::update()
{
    if (currentReloadTime > 0) currentReloadTime--;

    if (currentReloadTime == 0)
    {
        SoundManager::playSound(sound);

        if (attackPattern == 1)
        {
            for (int i = 0; i < 10; i++)
            {
                Bullet* bullet = new Bullet(x + (100 * i), y, 0, 1, 10, Side::ENEMY_SIDE);
                bullets.push_back(bullet);
                getScene()->addGameObject(bullet);
            }
            attackPattern--;
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                Bullet* bullet = new Bullet(x + (130 * i), y, 0, 1, 10, Side::ENEMY_SIDE);
                bullets.push_back(bullet);
                getScene()->addGameObject(bullet);
            }
            attackPattern++;
        }
        
        currentReloadTime = reloadTime;

    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPosY() > 1300 || bullets[i]->getPosX() < 0)
        {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
        }
    }
}

void Boss::draw()
{
	blit(texture, x, y);
}

int Boss::getPosX()
{
	return x;
}

int Boss::getPosY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

void Boss::getDamaged()
{
    health--;
}

int Boss::getHealth()
{
    return health;
}


void Boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Boss::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
