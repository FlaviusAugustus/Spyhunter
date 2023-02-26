#include "Enemy.h"

void Enemy::attack(int targetX, int targetY) {



	if (sprite.hitBox.y < targetY + sprite.hitBox.h * 2 && sprite.hitBox.y > targetY - sprite.hitBox.h * 2 && abs(sprite.hitBox.x - targetX) < sprite.hitBox.w * 5) {


		if (sprite.hitBox.x > targetX) {

			sprite.textureRect.x += -1;

		}
		else if (sprite.hitBox.x < targetX) {

			sprite.textureRect.x += 1;

		}

	}

}

