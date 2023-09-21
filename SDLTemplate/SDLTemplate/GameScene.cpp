#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Enemy();
		this->addGameObject(enemy);
		enemy->setPlayerTarget(player);

		spawnedEnemies.push_back(enemy);
	}
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
}
