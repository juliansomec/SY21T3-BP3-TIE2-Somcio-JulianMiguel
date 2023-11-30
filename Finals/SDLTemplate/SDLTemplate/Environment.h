#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"

class Environment : public GameObject
{
public:
	Environment();
	~Environment();
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

private:
	int x;
	int y;
	int width;
	int height;

	SDL_Texture* texture;
};

