#include "SDL.h"
#include "SDL_main.h"
#include "Timer.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"

Timer::Timer() {

	Paused = true;
	Started = false;

}

void Timer::init() {

	if (!Started) {

		time = 0;
		Paused = false;
		Started = true;
		startFrame = SDL_GetTicks();
		endFrame = 0; 

	}
}

void Timer::reset() {

	time = 0;
	startFrame = SDL_GetTicks();

}

bool Timer::isPaused() {

	return Paused;

}

void Timer::start() {

	if(Paused) {

		Paused = false;
		startFrame = SDL_GetTicks();

	}

}

void Timer::stop() {

	Paused = true;

}

void Timer::count() {

	double delta;

	if (!Paused && Started) {

		endFrame = SDL_GetTicks();
		delta = (endFrame - startFrame) * 0.001;

		startFrame = endFrame;
		time += delta;

	}

}

double Timer::getTime() {

	return time;

}

