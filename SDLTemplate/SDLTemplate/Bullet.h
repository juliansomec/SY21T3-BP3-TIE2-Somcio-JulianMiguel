#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Bullet : public GameObject
{
public:
	Bullet(float posX, float posY, float dirX, float dirY, float speed);
	void start();
	void update();
	void draw();
	float getPosX();
	float getPosY();
	float getWidth();
	float getHeight();
private:
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
};

