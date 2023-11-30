#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Environment.h"
#include "SoundManager.h"
#include "PowerUps.h"

class Goomba : public GameObject
{
public:
	~Goomba();
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void setPosX(int pos);
	void setPosY(int pos);

	bool getIsAlive();
	void doDeath();
	void setDirection();

	void setFloor(Environment* ground);
	bool isOnGround;

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Environment* floor;
	int x;
	int y;
	int width;
	int height;
	float speed;
	float directionX;
	int verticalSpeed;
	float gravity;
	bool isAlive;
};

