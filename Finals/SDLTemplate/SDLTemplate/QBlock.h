#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"

class QBlock : public GameObject
{
public:
	QBlock();
	~QBlock();

	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	bool getUsed();

	void setPosition(int x, int y);

	void QBlockUsed();
private:
	int x;
	int y;
	int width;
	int height;
	float gravity;

	bool isUsed;
	SDL_Texture* texture;
};

