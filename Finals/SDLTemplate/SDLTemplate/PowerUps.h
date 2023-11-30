#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"
#include "Environment.h"

enum class Type
{
	MUSHROOM,
	FLOWER
};

class PowerUps : public GameObject
{
public:
	PowerUps(int posX, int posY, float dirX, float dirY, float speed);
	~PowerUps();

	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void setPosY(int y);

	void setFloor(Environment* ground);
	bool isOnGround;
private:
	int x;
	int y;
	int width;
	int height;
	float directionX;
	float directionY;
	float speed;
	float gravity;
	float verticalSpeed;

	SDL_Texture* texture;
	Environment* floor;
};

