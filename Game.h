#pragma once
#include "Timer.h"
#include "Player.h"
#include "Road.h"
#include "Enemy.h"
#include "Neutral.h"

class Game {

	Timer playTime;
	Timer roadChangeTime;
	Timer enemySpawnTime;
	Timer penaltyTime;

public:

	int points;

	Player player;
	Road road;
	Enemy enemies[enemyCount];
	Neutral neutrals[neutralCount];

	bool isRunning;
	bool isPaused;
	bool quit;

	Game();

	void spawnEnemies();

	void moveEnemies();

	void countPoints();

	void playerInvincibilityCounter();

	void moveSprites();

	void changeRoad();

	void addPlayerLives();

	void handlePlayerEnemyCollisions();

	void isPlayerAlive();

	void attackPlayer();

	void checkBulletCollision();

	void checkPlayerOutOfBounds();

	void countTime();

	double getPlayTime();

	void pause();

	void unPause();

	void run(const Uint8* keyState);

	void end();

	void restart();

};