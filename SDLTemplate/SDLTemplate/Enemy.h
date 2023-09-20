#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void start();
	void update();
	void draw();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	float dirX;
	float dirY;
	int width;
	int height;
	int speed;
	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
	std::vector<Bullet*> bullets;
};

