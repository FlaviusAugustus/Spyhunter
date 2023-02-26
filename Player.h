#pragma once
#include"SDL.h"
#include"SDL_main.h"
#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Gun.h"

class Player {

private:

	int width;
	int height;

	int lives;
	int livesLost;
	bool isInvincible;

public:

	Sprite sprite;
	Gun gun;

	double velX;
	double velY;

	Player(int x, int y);

	void handleEvent(const Uint8* keyState);

	void move();

	bool checkCollision(SDL_Rect* rect);

	void destroyCar();

	void disableInvincibility();

	bool isDead();

	void setLives(int playerLives);

	void reset();

	void respawn();

private:

	void setHitbox();

};