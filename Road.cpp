#include <stdlib.h>
#include "SDL.h"
#include"SDL_main.h"
#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Road.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"

Road::Road() {

	SDL_Texture* roadNormal = nullptr;
	SDL_Texture* roadWide = nullptr;
	SDL_Texture* roadNarrow = nullptr;

	roadType = Normal;

	scroll = -5;

	roadBottom.textureRect.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadBottom.textureRect.y = ScreenHeight / 2 - roadHeight;
	roadBottom.textureRect.w = roadNormalWidth;
	roadBottom.textureRect.h = roadHeight;

	roadTop.textureRect.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadTop.textureRect.y = ScreenHeight / 2 - roadHeight;
	roadTop.textureRect.w = roadNormalWidth;
	roadTop.textureRect.h = roadHeight;

	roadBottom.hitBox.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadBottom.hitBox.y = ScreenHeight / 2 - roadHeight;
	roadBottom.hitBox.w = roadNormalWidth - 20;
	roadBottom.hitBox.h = roadHeight;

	roadTop.hitBox.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadTop.hitBox.y = ScreenHeight / 2 - roadHeight;
	roadTop.hitBox.w = roadNormalWidth - 20;
	roadTop.hitBox.h = roadHeight;

}

void Road::changeRoad() {

	roadType = rand() % MaxRoadTypes;

}

void Road::setRoad() {

	if (roadTop.texture != roadBottom.texture) {

		roadBottom.textureRect.w = roadTop.textureRect.w;
		roadBottom.textureRect.x = roadTop.textureRect.x;
		roadBottom.texture = roadTop.texture;

	}

	if (roadType == Wide) {

		roadTop.texture = roadWide;

		roadTop.textureRect.x = ScreenWidth / 2 - roadWideWidth / 2;
		roadTop.textureRect.w = roadWideWidth;

	}
	else if (roadType == Narrow) {

		roadTop.texture = roadNarrow;

		roadTop.textureRect.x = ScreenWidth / 2 - roadNarrowWidth / 2;
		roadTop.textureRect.w = roadNarrowWidth;

	}
	else if (roadType == Normal) {

		roadTop.texture = roadNormal;

		roadTop.textureRect.x = ScreenWidth / 2 - roadNormalWidth / 2;
		roadTop.textureRect.w = roadNormalWidth;

	}

}

void Road::scrollRoad(int offset) {

	scroll += offset;

	roadTop.textureRect.y = -roadTop.textureRect.h + scroll - 20;
	roadBottom.textureRect.y = scroll - 20;

	if (scroll > roadHeight) {

		scroll = -5;

		setRoad();

	}

	setHitbox();

}

void Road::setNormalRoad() {

	roadBottom.texture = roadNormal;
	roadTop.texture = roadNormal;

	roadBottom.textureRect.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadBottom.textureRect.y = ScreenHeight / 2 - roadHeight;
	roadBottom.textureRect.w = roadNormalWidth;
	roadBottom.textureRect.h = roadHeight;

	roadTop.textureRect.x = ScreenWidth / 2 - roadNormalWidth / 2;
	roadTop.textureRect.y = ScreenHeight / 2 - roadHeight;
	roadTop.textureRect.w = roadNormalWidth;
	roadTop.textureRect.h = roadHeight;

}

void Road::reset() {

	roadType = Normal;
	scroll = -5;
	setNormalRoad();

}

void Road::setHitbox() {

	roadBottom.hitBox.w = roadBottom.textureRect.w - 20;
	roadBottom.hitBox.x = ScreenWidth / 2 - roadBottom.hitBox.w / 2;
	roadBottom.hitBox.y = roadBottom.textureRect.y;

	roadTop.hitBox.w = roadTop.textureRect.w - 20;
	roadTop.hitBox.x = ScreenWidth / 2 - roadTop.hitBox.w / 2;
	roadTop.hitBox.y = roadTop.textureRect.y;

}

