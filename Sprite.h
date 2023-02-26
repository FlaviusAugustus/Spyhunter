#pragma once
#include "SDL.h"
#include "SDL_main.h"

//texture rect is the rect in which the texture is rendered, hitbox is used 
//to detect collisions between sprites and is slightly smaller than textureRect
struct Sprite {

	SDL_Texture* texture;
	SDL_Rect textureRect;
	SDL_Rect hitBox;

};