#include <stdlib.h>
#include "SDL.h"
#include"SDL_main.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"
#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Car.h"
#include "Road.h"



Car::Car() {

	velX = 0;
	velY = 0;
	isAlive = false;

}

void Car::spawn(int spawnAreaStart, int spawnAreaWidth) {

	isAlive = true;
	sprite.textureRect.w = 36;
	sprite.textureRect.h = 60;

	int side = rand() % 2;

	sprite.textureRect.x = spawnAreaStart + rand() % spawnAreaWidth;

	if (side == 1) {

		sprite.textureRect.y = ScreenHeight + 40;

	}
	else {

		sprite.textureRect.y = -40;

	}
	if (sprite.textureRect.y < 0) {

		velY = 5.5 + rand() % 4;

	}

	else if (sprite.textureRect.y > ScreenHeight) {

		velY = 11 + rand() % 3;

	}
}

void Car::move(Road* road, int offset) {

	if (isAlive) {

		if (sprite.textureRect.x < road->roadTop.textureRect.x) {

			velX = 3;

		}
		else if (sprite.textureRect.x + 60 > road->roadTop.textureRect.x + road->roadTop.textureRect.w) {

			velX = -3;

		}
		else {

			velX = 0;
		}

		sprite.textureRect.y += -velY + offset;
		sprite.textureRect.x += velX;

		setHitbox();

	}
}

void Car::killStranded() {

	if (sprite.hitBox.y >= 2 * ScreenHeight || sprite.hitBox.y <= -2 * ScreenHeight) {
		isAlive = false;
	}

}

void Car::kill() {

	isAlive = false;
	sprite.textureRect.x = -10;
	sprite.textureRect.y = -10;

	setHitbox();

}

void Car::setHitbox() {

	sprite.hitBox.w = sprite.textureRect.w - 10;
	sprite.hitBox.h = sprite.textureRect.h;

	sprite.hitBox.x = sprite.textureRect.x + sprite.textureRect.w / 2 - sprite.hitBox.w / 2;
	sprite.hitBox.y = sprite.textureRect.y + sprite.textureRect.h / 2 - sprite.hitBox.h / 2;

}
