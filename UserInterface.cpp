#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "SDL_main.h"
#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Rgb.h"
#include "Game.h"
#include "UserInterface.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"


UserInterface::UserInterface() {

	window = nullptr;
	screenSurface = nullptr;
	renderer = nullptr;
	charSet = nullptr;
	keyState = SDL_GetKeyboardState(NULL);

}

UserInterface::~UserInterface() {

	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);
	
}

bool UserInterface::loadTexture(const char* path, SDL_Texture** texture) {

	SDL_Surface* image = SDL_LoadBMP(path);

	if (!image)
	{
		return false;
	}

	*texture = SDL_CreateTextureFromSurface(renderer, image);

	if (!*texture)
	{
		return false;
	}

	SDL_FreeSurface(image);

	return true;
}

bool UserInterface::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		return false;

	}
	else {

		SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, 0, &window, &renderer);

		if (window == nullptr || renderer == nullptr) {

			return false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}

	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_RenderSetLogicalSize(renderer, ScreenWidth, ScreenHeight);
	SDL_SetWindowTitle(window, "Grzech Gracjan 193579");

	return true;

}

void UserInterface::DrawTexture(Sprite sprite) {

	SDL_RenderCopy(renderer, sprite.texture, NULL, &sprite.textureRect);

}

void UserInterface::DrawPixel(int x, int y, colorRGB color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
	SDL_RenderDrawPoint(renderer, x, y);
}

void UserInterface::DrawLine(int x1, int y1, int x2, int y2, colorRGB color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void UserInterface::DrawRectangle(int x, int y, int l, int k, colorRGB out, colorRGB in) {

	SDL_Rect rectFill = { x, y, l, k };

	SDL_SetRenderDrawColor(renderer, out.r, out.g, out.b, 0);
	SDL_RenderDrawRect(renderer, &rectFill);

	rectFill.x++;
	rectFill.y++;
	rectFill.w -= 2;
	rectFill.h -= 2;

	SDL_SetRenderDrawColor(renderer, in.r, in.g, in.b, 0);
	SDL_RenderFillRect(renderer, &rectFill);
}

void UserInterface::quit(SDL_Window** window, SDL_Surface** surface) {
	SDL_FreeSurface(*surface);
	*surface = nullptr;

	SDL_DestroyWindow(*window);
	*window = nullptr;

	SDL_Quit();
}

void UserInterface::DrawString(int x, int y, const char* text) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_RenderCopy(renderer, charSet, &s, &d);
		x += 8;
		text++;
	}
}

void UserInterface::changeBackgroundColor() {

	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 0);
}

void UserInterface::drawScene() {

	SDL_RenderPresent(renderer);
}

void UserInterface::clearScreen() {

	SDL_RenderClear(renderer);
}

void UserInterface::renderUI(double playTime, int points) {

	DrawRectangle(ScreenWidth / 2 - 100, 4, 200, 100, grey, black);
	DrawRectangle(ScreenWidth - 204, ScreenHeight - 104, 200, 100, grey, black);

	DrawString(ScreenWidth - 182, ScreenHeight - 68, "Implemented elements");
	DrawString(ScreenWidth - 188, ScreenHeight - 52, "a b c d e f h i j k m");
	sprintf(buffer, "Time: %.1f", playTime);
	DrawString(ScreenWidth / 2 - 45, 45, buffer);
	sprintf(buffer, "Points: %d", points);
	DrawString(ScreenWidth / 2 - 45, 45 + 18, buffer);
}

void UserInterface::renderPauseScreen() {

	DrawRectangle(ScreenWidth / 2 - 200, 200, 400, 200, grey, black);
	DrawString(ScreenWidth / 2 - 40, 295, "GAME PAUSED");
	DrawString(ScreenWidth / 2 - 40, 311, "___________");
	drawScene();
}

void UserInterface::renderGame(Game* game) {

	DrawTexture(game->road.roadBottom);
	DrawTexture(game->road.roadTop);

	for (int i = 0; i < enemyCount; i++) {

		if (game->enemies[i].isAlive) {

			DrawTexture(game->enemies[i].sprite);
		}
	}

	DrawTexture(game->player.sprite);

	for (int i = 0; i < bulletCount; i++) {

		if (game->player.gun.bullets[i].isShot) {
			DrawTexture(game->player.gun.bullets[i].sprite);
		}
	}

	for (int i = 0; i < neutralCount; i++) {

		if (game->neutrals[i].isAlive) {
			DrawTexture(game->neutrals[i].sprite);
		}
	}

}

void UserInterface::renderDeathScreen(int points) {

	bool isVisible = true;

	while (isVisible) {

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {

				;

			}
			if (event.type == SDL_KEYDOWN) {

				if (event.key.keysym.sym == SDLK_SPACE) {

					isVisible = false;

				}
			}

		}

		SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
		SDL_RenderClear(renderer);

		DrawRectangle(ScreenWidth / 2 - 200, 200, 400, 200, grey, black);
		DrawString(ScreenWidth / 2 - 35, 295, "YOU LOST");
		sprintf(buffer, "SCORE: %d", points);
		DrawString(ScreenWidth / 2 - 40, 311, buffer);
		DrawString(ScreenWidth / 2 - 75, 327, "Press space to restart");
		drawScene();

	}
}

const Uint8* UserInterface::getKeyboardState() {

	SDL_PumpEvents();
	return keyState;

}

void UserInterface::render(Game* game) {

	clearScreen();
	renderGame(game);
	renderUI(game->getPlayTime(), game->points);
	changeBackgroundColor();
	drawScene();

}

bool UserInterface::loadGameTextures(Game* game) {

	if (!loadTexture(roadPath, &game->road.roadNormal) || !loadTexture(PlayerCarPath, &game->player.sprite.texture) || !loadTexture(charSetPath, &charSet)
		|| !loadTexture(roadWidePath, &game->road.roadWide) || !loadTexture(roadNarrowPath, &game->road.roadNarrow)) {

		return false;
	}

	for (int i = 0; i < enemyCount; i++) {

		if (!loadTexture(EnemyCarPath, &game->enemies[i].sprite.texture)) {

			return false;

		}

	}

	for (int i = 0; i < neutralCount; i++) {

		if (!loadTexture(NeutralCarPath, &game->neutrals[i].sprite.texture)) {

			return false;

		}
	}

	for (int i = 0; i < bulletCount; i++) {

		if (!loadTexture(bulletPath, &game->player.gun.bullets[i].sprite.texture)) {

			return false;

		}

	}

	return true;

}
