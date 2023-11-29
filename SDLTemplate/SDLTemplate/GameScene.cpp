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
	currentExplodeTimer = 11;
	pSpawnTimer = 1000;
	pCurrentSpawnTimer = 1000;
	waveCount = 0;
	bossSpawned = false;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();

	blit(texture, 1920, 1080);
	drawText(110, 120, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

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
	powerUpLogic();
}

void GameScene::spawnLogic()
{
	if (waveCount % 5 == 0 && waveCount != 0)
	{
		spawnBoss();
		waveCount = 0;
	}
	else if (!bossSpawned)
	{
		if (currentSpawnTimer > 0) currentSpawnTimer--;

		if (currentSpawnTimer <= 0)
		{
			for (int i = 0; i < 3; i++)
			{
				spawn();
			}
			waveCount++;
			currentSpawnTimer = spawnTime;
		}

		for (int i = 0; i < spawnedEnemies.size(); i++)
		{
			if (spawnedEnemies[i]->getPosY() > 1300)
			{
				Enemy* enemiesToErase = spawnedEnemies[i];
				spawnedEnemies.erase(spawnedEnemies.begin() + i);
				delete enemiesToErase;

				break;
			}
		}
	}
	
}

void GameScene::spawnBoss()
{
	Boss* boss = new Boss();
	this->addGameObject(boss);
	boss->setPlayerTarget(player);

	boss->setPosition(boss->getPosX(), boss->getPosY());
	spawnedBoss.push_back(boss);
	bossSpawned = true;
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
						break;
					}
				}

				for (int i = 0; i < spawnedBoss.size(); i++)
				{
					Boss* boss = spawnedBoss[i];
					int collision = checkCollision(
						boss->getPosX(), boss->getPosY(), boss->getWidth(), boss->getHeight(),
						bullet->getPosX(), bullet->getPosY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						boss->getDamaged();
						std::cout << boss->getHealth() << std::endl;
						if (boss->getHealth() <= 0)
						{
							delete boss;
							bossSpawned = 0;
						}
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

	enemy->setPosition(0 + (rand() % 500), 0);
	spawnedEnemies.push_back(enemy);
	std::cout << waveCount << std::endl;
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

void GameScene::spawnPowerUp()
{
	PowerUp* powerUp = new PowerUp();
	this->addGameObject(powerUp);
	
	powerUp->setPosition(rand() % 400 + 50, 0);
	spawnedPowerUps.push_back(powerUp);
}



void GameScene::powerUpLogic()
{
	if (pCurrentSpawnTimer > 0) pCurrentSpawnTimer--;

	if (pCurrentSpawnTimer <= 0)
	{
		for (int i = 0; i < 1; i++)
		{
			spawnPowerUp();
			std::cout << "Spawned power up" << std::endl;
		}
 		pCurrentSpawnTimer = pSpawnTimer;
	}

	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		PowerUp* powerUp = dynamic_cast<PowerUp*>(spawnedPowerUps[i]);

		int collision = checkCollision(
			player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
			powerUp->getPosX(), powerUp->getPosY(), 3, 3
		);

		if (collision == 1)
		{
			collectPowerUp(powerUp);
		}
	}
}

void GameScene::collectPowerUp(PowerUp* powerUp)
{
	int index = -1;
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (powerUp == spawnedPowerUps[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		player->collectPowerUps();
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete powerUp;
	}
}


//Notes:
//Will die after a few hits