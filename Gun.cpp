#include "Gun.h"



void Gun::shoot(int refX, int refY) {

	for (int i = 0; i < bulletCount; i++) {

		if (!bullets[i].isShot) {
			bullets[i].shoot(refX, refY);
			break;

		}

	}
}

void Gun::moveBullets(int refY) {

	for (int i = 0; i < bulletCount; i++) {

		if (bullets[i].isShot) {

			bullets[i].move(refY);

		}

	}

}
