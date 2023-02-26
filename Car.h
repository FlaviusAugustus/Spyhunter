#pragma once
#include"SDL.h"
#include"SDL_main.h"
#include "Sprite.h"
#include "Road.h"

class Car {

protected:

	double velX;
	double velY;

public:

	Sprite sprite;
	bool isAlive;

	Car();

	void spawn(int spawnAreaStart, int spawnAreaWidth);

	void move(Road* road, int offset);

	void killStranded();

	void kill();

private:

	void setHitbox();

};