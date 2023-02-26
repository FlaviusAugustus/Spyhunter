#pragma once
#include <stdio.h>
#include "SDL.h"
#include "SDL_main.h"
#include "SpyHunterConstants.h"
#include "Rgb.h"
#include "Sprite.h"
#include "Game.h"



class UserInterface {

	char buffer[maxBufferSize];
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	const Uint8* keyState;

public:

	SDL_Texture* charSet;

	SDL_Event event;

	UserInterface();

	~UserInterface();

	bool loadTexture(const char* path, SDL_Texture** texture);

	bool loadGameTextures(Game* game);

	bool init();

	void DrawTexture(Sprite sprite);

	void DrawPixel(int x, int y, colorRGB color);

	void DrawLine(int x1, int y1, int x2, int y2, colorRGB color);

	void DrawRectangle(int x, int y, int l, int k, colorRGB out, colorRGB in);

	void quit(SDL_Window** window, SDL_Surface** surface);

	void DrawString(int x, int y, const char* text);

	void changeBackgroundColor();

	void drawScene();

	void clearScreen();

	void renderUI(double playTime, int points);

	void renderPauseScreen();

	void renderGame(Game* game);

	void renderDeathScreen(int points);

	const Uint8* getKeyboardState();

	void render(Game* game);

};