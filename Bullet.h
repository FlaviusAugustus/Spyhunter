#pragma once
#include "Sprite.h"

class Bullet {

	int vel;
	int range;

public:

	Sprite sprite;
	bool isShot;


	Bullet();

	void shoot(int refX, int refY);

	void move(int refY);

private:

	void setHitbox();

};

