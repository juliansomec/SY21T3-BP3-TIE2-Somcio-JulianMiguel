#pragma once
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Environment.h"
#include "Bricks.h"
#include "QBlock.h"
#include "PowerUps.h"
#include "Goomba.h"
#include "text.h"
#include "Block.h"
#include "SoundManager.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

	void collisionCheck();
	void spawnBlocks(int x);
	void despawnBricks(Bricks* brick);

	void spawnPowerUps();

	void goombaSpawn();
	void goombaSpawnLogic();
	void goombaDeath(Goomba* goomba);

	void addBlocks();
private:
	Player* player;
	Environment* floor;
	QBlock* qblock;
	SoundManager* music;

	std::vector<Bricks*> spawnedBricks;
	std::vector<PowerUps*> spawnedPowerUps;
	std::vector<Goomba*> spawnedGoombas;
	std::vector<Block*> spawnedBlocks;

	int currentSpawnTimer;
	int spawnTimer;
	int side;
	int points;
};

