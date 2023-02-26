#pragma once
#include "SDL.h"
#include"SDL_main.h"
#include "Sprite.h"

enum roadTypes {
	Normal,
	Wide,
	Narrow,
	MaxRoadTypes
};

class Road {

	int roadType;

	int scroll;

public:

	SDL_Texture* roadNormal;
	SDL_Texture* roadWide;
	SDL_Texture* roadNarrow;

	Sprite roadTop;
	Sprite roadBottom;

	Road();

	void changeRoad();

	void setRoad();

	void scrollRoad(int offset);

	void setNormalRoad();

	void reset();

private:

	void setHitbox();

		
};