#include "Bullet.h"

Bullet::Bullet() {

	vel = 10;
	range = 100;
	isShot = false;

}

void Bullet::shoot(int refX, int refY) {

	isShot = true;
	sprite.textureRect.w = 10;
	sprite.textureRect.h = 10;
	sprite.textureRect.x = refX + sprite.textureRect.w / 2;
	sprite.textureRect.y = refY;

}

void Bullet::move(int refY) {

	sprite.textureRect.y -= vel;

	if (refY - sprite.textureRect.y > range) {

		isShot = false;
		sprite.textureRect.x = -20;
		sprite.textureRect.y = -20;

	}

	setHitbox();

}



void Bullet::setHitbox() {

	sprite.hitBox.w = sprite.textureRect.w - 5;
	sprite.hitBox.h = sprite.textureRect.h - 5;

	sprite.hitBox.x = sprite.textureRect.x + sprite.textureRect.w / 2 - sprite.hitBox.w / 2;
	sprite.hitBox.y = sprite.textureRect.y + sprite.textureRect.h / 2 - sprite.hitBox.h / 2;
}


