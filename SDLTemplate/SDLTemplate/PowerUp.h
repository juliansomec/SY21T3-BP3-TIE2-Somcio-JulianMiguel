#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "draw.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

class PowerUp : public GameObject
{
public:
	PowerUp();
	~PowerUp();
	void start();
	void draw();
	void update();
	void setPosition(int xPos, int yPos);
	int getPosX();
	int getPosY();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* player;
	int width;
	int height;
	int x;
	int y;
};

