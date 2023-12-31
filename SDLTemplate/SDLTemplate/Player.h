#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>  

class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();
	void collectPowerUps();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float reloadTime;
	float currentReloadTime;
	float specReloadTime;
	float currentSpecReloadTime;
	std::vector<Bullet*> bullets;
	bool isAlive;

	int currentPowerUps;
};

