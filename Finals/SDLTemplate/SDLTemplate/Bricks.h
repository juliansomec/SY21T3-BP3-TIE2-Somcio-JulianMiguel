#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"

class Bricks : public GameObject
{
public:
	Bricks();
	~Bricks();

	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void setPosition(int x, int y);
private:
	int x;
	int y;
	int width;
	int height;

	SDL_Texture* texture;
};

