#include"SDL.h"
#include"SDL_main.h"
#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Player.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"

Player::Player(int x, int y) {

	width = 36;
	height = 60;

	lives = 1;
	livesLost = 0;

	isInvincible = true;

	velX = 0;
	velY = 0;

	sprite.textureRect.w = width;
	sprite.textureRect.h = height;
	sprite.textureRect.x = x - width / 2;
	sprite.textureRect.y = y - height / 2;

}

void Player::handleEvent(const Uint8* keyState)
{

	SDL_PumpEvents();

	if (!keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT]) {
		velX = 0;
	}

	if (keyState[SDL_SCANCODE_UP] == NULL && !keyState[SDL_SCANCODE_DOWN] == NULL) {
		velY -= maxAcc;
	}

	if (keyState[SDL_SCANCODE_UP]) {
		velY += maxAcc;
	}
	else {
		velY -= maxAcc * 0.2;
	}
	 
	if (keyState[SDL_SCANCODE_DOWN]) {
		velY += -maxAcc;

	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		velX = -maxVelX;
	}
	if (keyState[SDL_SCANCODE_RIGHT]) {
		velX = maxVelX;
	}

	if (keyState[SDL_SCANCODE_SPACE]) {

		gun.shoot(sprite.textureRect.x + sprite.textureRect.w/2 - gun.bullets[0].sprite.textureRect.w, sprite.textureRect.y);

	}

}

void Player::move() {

	if (velY >= maxVelY) {
		velY = maxVelY;
	}
	else if (velY <= 0) {
		velY = 0;
	}

	sprite.textureRect.x += velX;
	gun.moveBullets(sprite.textureRect.y);

	setHitbox();
}

bool Player::checkCollision(SDL_Rect* rect) {

	return SDL_HasIntersection(&sprite.hitBox, rect);

}

void Player::destroyCar() {

	if (!isInvincible) {
		livesLost++;
	}

}

void Player::disableInvincibility() {

	isInvincible = false;

}

void Player::setLives(int Playerlives) {

	lives = 1 + Playerlives;

}

bool Player::isDead() {

	return lives - livesLost <= 0;
}

void Player::reset() {

	velX = 0;
	velY = 0;
	sprite.textureRect.x = ScreenWidth / 2;
	sprite.textureRect.y = 2 * ScreenHeight / 3;

}

void Player::respawn() {

	reset();
	isInvincible = true;
	lives = 1;
	livesLost = 0;

}



void Player::setHitbox() {

	sprite.hitBox.w = sprite.textureRect.w - 10;
	sprite.hitBox.h = sprite.textureRect.h - 30;

	sprite.hitBox.x = sprite.textureRect.x + sprite.textureRect.w / 2 - sprite.hitBox.w / 2;
	sprite.hitBox.y = sprite.textureRect.y + sprite.textureRect.h / 2 - sprite.hitBox.h / 2;

}


