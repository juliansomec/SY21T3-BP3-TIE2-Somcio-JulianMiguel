#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerUp.h"
#include "Boss.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;

	float spawnTime;
	float currentSpawnTimer;
	float explodeTimer;
	float currentExplodeTimer;
	float pSpawnTimer;
	float pCurrentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUp*> spawnedPowerUps;
	std::vector<Boss*> spawnedBoss;

	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnLogic();
	void collisionLogic();

	void spawnBoss();
	void bossCollision(Boss* boss);
	bool bossSpawned;

	void spawnPowerUp();
	void powerUpLogic();
	void collectPowerUp(PowerUp* powerUp);

	int points;
	int height;
	int width;
	int waveCount;
	SDL_Texture* texture;
};

