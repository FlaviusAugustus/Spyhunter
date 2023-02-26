#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include<cmath>
#include<stdio.h>
#include<string.h>
#include <time.h>
#include <cstring>
#include "SDL.h"
#include "SDL_main.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"

#include "SpyHunterConstants.h"
#include "Sprite.h"
#include "Rgb.h"
#include "Road.h"
#include "Player.h"
#include "Car.h"
#include "Enemy.h"
#include "Neutral.h"
#include "Timer.h"
#include "Game.h"
#include "UserInterface.h"





int main(int argc, char** argv) {

	srand(time(NULL));

	UserInterface ui;

	if (!ui.init()) {

		return 1;

	}

	Game game;

	if (!ui.loadGameTextures(&game)) {

		return 1;

	}

	while (!game.quit) {

		if (!game.isRunning) {

			ui.renderDeathScreen(game.points);

		}

		game.restart();

		while (game.isRunning) {

			SDL_Delay(5);

			game.countTime();

			while (SDL_PollEvent(&ui.event)) {
				if (ui.event.type == SDL_QUIT) {
					game.end();
				}
				if (ui.event.type == SDL_KEYDOWN && ui.event.key.keysym.sym == SDLK_ESCAPE) {

					game.pause();
					ui.renderPauseScreen();

					while (game.isPaused) {
						SDL_PollEvent(&ui.event);
						if (ui.event.type == SDL_QUIT) {

							game.end();
						}
						if (ui.event.type == SDL_KEYDOWN && ui.event.key.keysym.sym == SDLK_ESCAPE
							&& !ui.event.key.repeat) {

							game.unPause();
						}
					}
				}
				if (ui.event.type == SDL_KEYDOWN && ui.event.key.keysym.sym == SDLK_n) {

					game.restart();

				}

			}

			game.run(ui.getKeyboardState());
			ui.render(&game);

		}
	}
	return 0;
};
