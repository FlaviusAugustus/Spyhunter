#pragma once
#include "SpyHunterConstants.h"
#include "Bullet.h"


class Gun {


public:

	Bullet bullets[bulletCount];

	void shoot(int refX, int refY);

	void moveBullets(int refY);

};