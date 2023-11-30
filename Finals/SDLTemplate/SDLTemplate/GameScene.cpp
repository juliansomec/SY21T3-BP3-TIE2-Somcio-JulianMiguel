#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	floor = new Environment();
	this->addGameObject(floor);

	player->setFloor(floor);

	qblock = new QBlock();
	this->addGameObject(qblock);



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

	for (int i = 0; i < 3; i++)
	{
		spawnBlocks(90 * i);
	}

	initFonts();
	qblock->setPosition(1000, 400);

	spawnTimer = 50;
	currentSpawnTimer = 0;
	side = 1;
}

void GameScene::draw()
{
	Scene::draw();

	
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (spawnedBricks.size() > 0)
	{
		drawText(640, 20, 255, 255, 255, TEXT_CENTER, "BREAK ALL THE BRICKS!");
	}

	if (!player->getIsAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}

}

void GameScene::update()
{ 
	Scene::update();

	collisionCheck();

	if (spawnedBricks.size() <= 0)
	{
		goombaSpawnLogic();
		addBlocks();
	}

}


void GameScene::collisionCheck()
{
	//player collision
	int collision = checkCollision(
		player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
		floor->getPosX(), floor->getPosY(), floor->getWidth(), floor->getHeight()
	);

	if (collision == 1 && player->getPosY() + player->getHeight() > floor->getPosY())
	{
		if (player->getPosY() + player->getHeight() >= floor->getPosY())
		{
			player->setPosY(floor->getPosY() - player->getHeight());
			player->isOnGround = true;
		}
		else
		{
			player->isOnGround = false;																																					
		}
	}

	//bricks collision
	for (int i = 0; i < objects.size(); i++)
	{
		Bricks* brick = dynamic_cast<Bricks*>(objects[i]);

		if (brick)
		{
			int walkBrickCollision = checkCollision(
				brick->getPosX(), brick->getPosY(), brick->getWidth(), brick->getHeight() / 2,
				player->getPosX(), player->getPosY() + player->getHeight() / 2, player->getWidth(), player->getHeight() / 2
			);

			int breakBrickCollision = checkCollision(
				brick->getPosX(), brick->getPosY() + brick->getHeight() / 2, brick->getWidth(), brick->getHeight() / 2,
				player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight() / 2
			);

			if (walkBrickCollision == 1 && player->getPosY() + player->getHeight() > brick->getPosY())
			{
				player->setPosY(brick->getPosY() - player->getHeight());
				player->isOnGround = true;
			}
			
			if (breakBrickCollision == 1 && player->getIsTall())
			{
				if (breakBrickCollision == 1)
				{
					despawnBricks(brick);
				}
			}
			else if (breakBrickCollision == 1 && !player->getIsTall())
			{
				player->setPosY(brick->getPosY() + player->getHeight());
				player->isOnGround = true;
			}
		}
	}

	int qBlockCollision = checkCollision(
		qblock->getPosX(), qblock->getPosY(), qblock->getWidth(), qblock->getHeight(),
		player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight() / 2
	);

	if (qBlockCollision == 1)
	{
		player->setPosY(qblock->getPosY() + player->getHeight());
		spawnPowerUps();
		qblock->QBlockUsed();
	}

	//power ups collision
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		PowerUps* powerUp = spawnedPowerUps[i];

		int terrainPowerUpCollision = checkCollision(
			powerUp->getPosX(), powerUp->getPosY(), powerUp->getWidth(), powerUp->getHeight(),
			floor->getPosX(), floor->getPosY(), floor->getWidth(), floor->getHeight()
		);

		if (terrainPowerUpCollision == 1)
		{
			if (powerUp->getPosY() + powerUp->getHeight() >= floor->getPosY())
			{
				powerUp->setPosY(floor->getPosY() - powerUp->getHeight());
				powerUp->isOnGround = true;
			}
			else
			{
				powerUp->isOnGround = false;
			}
		}

		int playerPowerUpCollision = checkCollision(
			powerUp->getPosX(), powerUp->getPosY(), powerUp->getWidth(), powerUp->getHeight(),
			player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight()
		);

		if (playerPowerUpCollision == 1)
		{
			player->collectPowerUp();
			delete powerUp;
		}
	}

	// goomba collision
	for (int i = 0; i < spawnedGoombas.size(); i++)
	{
		Goomba* goomba = spawnedGoombas[i];

		int goombaFloorCollision = checkCollision(
			goomba->getPosX(), goomba->getPosY(), goomba->getWidth(), goomba->getHeight(),
			floor->getPosX(), floor->getPosY(), floor->getWidth(), floor->getHeight()
		);

		int goombaPlayerCollision = checkCollision(
			goomba->getPosX(), goomba->getPosY(), goomba->getWidth(), goomba->getHeight(),
			player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight()
		);

		if (goombaFloorCollision == 1)
		{
			if (goomba->getPosY() + goomba->getHeight() >= floor->getPosY())
			{
				goomba->setPosY(floor->getPosY() - goomba->getHeight());
				goomba->isOnGround = true;
			}

			if (goombaPlayerCollision == 1 && goombaFloorCollision == 1)
			{
				player->doDeath();
				break;
			}
		}

		int playerStompCollision = checkCollision(
			goomba->getPosX(), goomba->getPosY(), goomba->getWidth(), goomba->getHeight() / 2,
			player->getPosX(), player->getPosY() + player->getHeight() / 2, player->getWidth(), player->getHeight()
		);

		if (playerStompCollision == 1)
		{
			goombaDeath(goomba);
			points++;
		}
	}

	for (int i = 0; i < spawnedBlocks.size(); i++)
	{
		Block* block = spawnedBlocks[i];

		int blockCollision = checkCollision(
			block->getPosX(), block->getPosY(), block->getWidth(), block->getHeight(),
			player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight()
		);

		if (blockCollision == 1)
		{
			if (player->getPosY() + player->getHeight() >= block->getPosY())
			{
				player->setPosY(block->getPosY() - player->getHeight());
				player->isOnGround = true;
			}
			else
			{
				player->isOnGround = false;
			}
		}
	}
}

void GameScene::spawnBlocks(int x)
{
	Bricks* brick = new Bricks();
	this->addGameObject(brick);
	brick->setPosition(400 + x, 400);
	spawnedBricks.push_back(brick);
}

void GameScene::despawnBricks(Bricks* brick)
{
	int index = -1;
	for (int i = 0; i < spawnedBricks.size(); i++)
	{
		if (brick == spawnedBricks[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedBricks.erase(spawnedBricks.begin() + index);
		delete brick;
	}
}

void GameScene::spawnPowerUps()
{
	if (!qblock->getUsed())
	{
		PowerUps* powerUp = new PowerUps(qblock->getPosX() - qblock->getWidth() / 2, qblock->getPosY() - qblock->getHeight(), -1, 0, 3);
		this->addGameObject(powerUp);
		spawnedPowerUps.push_back(powerUp);
	}
}

void GameScene::goombaSpawn()
{
	//1 = left side, 2 = right side
	if (side % 2 == 0)
	{
		Goomba* goomba = new Goomba();
		this->addGameObject(goomba);
		goomba->setPosX(-70);
		spawnedGoombas.push_back(goomba);
	}
	else
	{
		Goomba* goomba = new Goomba();
		this->addGameObject(goomba);
		goomba->setPosX(1300);
		goomba->setDirection();
		spawnedGoombas.push_back(goomba);
	}
}

void GameScene::goombaSpawnLogic()
{
	if (currentSpawnTimer > 0) currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 1; i++)
		{
			goombaSpawn();
			side++;
		}
		currentSpawnTimer = spawnTimer;
	}

	for (int i = 0; i < spawnedGoombas.size(); i++)
	{
		if (spawnedGoombas[i]->getPosX() > 1400 || spawnedGoombas[i]->getPosX() < -100)
		{
			Goomba* goombasToErase = spawnedGoombas[i];
			spawnedGoombas.erase(spawnedGoombas.begin() + i);
			delete goombasToErase;

			break;
		}
	}
}

void GameScene::goombaDeath(Goomba* goomba)
{
	int index = -1;
	for (int i = 0; i < spawnedGoombas.size(); i++)
	{
		if (goomba == spawnedGoombas[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedGoombas.erase(spawnedGoombas.begin() + index);
		delete goomba;
	}
}

void GameScene::addBlocks()
{
	Block* block1 = new Block();
	this->addGameObject(block1);
	block1->setPosition(400, 230);
	spawnedBlocks.push_back(block1);

	Block* block2 = new Block();
	this->addGameObject(block2);
	block2->setPosition(550, 230);
	spawnedBlocks.push_back(block2);

	Block* block3 = new Block();
	this->addGameObject(block3);
	block3->setPosition(700, 230);
	spawnedBlocks.push_back(block3);

	Block* block4 = new Block();
	this->addGameObject(block4);
	block4->setPosition(0, 520);
	spawnedBlocks.push_back(block4);

	Block* block5 = new Block();
	this->addGameObject(block5);
	block5->setPosition(200, 350);
	spawnedBlocks.push_back(block5);
}


