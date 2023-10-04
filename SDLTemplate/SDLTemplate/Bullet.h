#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

enum class Side
{
	PLAYER_SIDE,
	ENEMY_SIDE
};

class Bullet : public GameObject
{
public:
	Bullet(float posX, float posY, float dirX, float dirY, float speed, Side side);
	void start();
	void update();
	void draw();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	Side getSide();
private:
	SDL_Texture* texture;
	Side side;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
};

