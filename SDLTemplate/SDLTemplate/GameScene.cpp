#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	
	// Initialize any scene logic here

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300;
	explodeTimer = 11;
	currentExplodeTimer = 5;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	blit(texture, 1920, 1080);
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (!player->getIsAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();

	spawnLogic();
	collisionLogic();
}

void GameScene::spawnLogic()
{
	if (currentSpawnTimer > 0) currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}
		currentSpawnTimer = spawnTime;
	}

	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->getPosX() < -70)
		{
			Enemy* enemiesToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemiesToErase;

			break;
		}
	}
}

void GameScene::collisionLogic()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
					bullet->getPosX(), bullet->getPosY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPosX(), currentEnemy->getPosY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPosX(), bullet->getPosY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						currentEnemy->explodeState();

						if (currentExplodeTimer > 0) currentExplodeTimer--;

						if (currentExplodeTimer <= 0)
						{
							despawnEnemy(currentEnemy);
							currentExplodeTimer = explodeTimer;
						}
						points++;
						// only despawn one at a time
						// otherwise we might crash due to looping while deleting a null pointer
						break;
					}
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1300, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}
