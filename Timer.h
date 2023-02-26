#pragma once

class Timer {

	double startFrame;
	double endFrame;
	double pauseFrame;

	double time;

	bool Paused;
	bool Started;

public:

	Timer();

	void init();

	void reset();

	void start();

	void stop();

	void count();

	bool isPaused();

	double getTime();

};
