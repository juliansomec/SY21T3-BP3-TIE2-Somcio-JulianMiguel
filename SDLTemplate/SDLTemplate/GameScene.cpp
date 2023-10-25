#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

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

	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet->getSide() == Side::ENEMY_SIDE)
		{
			int collision = checkCollision(
				player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
				bullet->getPosX(), bullet->getPosY(), bullet->getWidth(), bullet->getHeight()
				);

			if (collision == 1)
			{
				std::cout << "Player has been hit!" << std::endl;
				break;
			}
		}
		if (bullet->getSide() == Side::PLAYER_SIDE)
		{

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
