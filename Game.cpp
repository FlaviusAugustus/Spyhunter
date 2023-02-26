#include <stdlib.h>
#include "SDL.h"
#include "SDL_main.h"
//#include "./SDL2-2.0.10/include/SDL.h"
//#include "./SDL2-2.0.10/include/SDL_main.h"
#include "Timer.h"
#include "Player.h"
#include "Road.h"
#include "Enemy.h"
#include "Game.h"
#include <stdio.h>



Game::Game() : player(ScreenWidth / 2, 2 * ScreenHeight / 3) {

	playTime.init();
	roadChangeTime.init();
	enemySpawnTime.init();
	penaltyTime.init();
	penaltyTime.stop();

	isRunning = true;
	quit = false;
	isPaused = false;

	points = 0;

	road.setNormalRoad();

}

void Game::spawnEnemies() {

	if (enemySpawnTime.getTime() > 2 + rand() % 4) {
		
		int type = rand() % 2;

		if (type == 0) {

			for (int i = 0; i < enemyCount; i++) {

				if (!enemies[i].isAlive) {
					enemies[i].spawn(road.roadTop.hitBox.x, road.roadTop.hitBox.w);
					break;
				}
			}
		}

		if (type == 1) {

			for (int i = 0; i < neutralCount; i++) {

				if (!neutrals[i].isAlive) {
					neutrals[i].spawn(road.roadTop.hitBox.x, road.roadTop.hitBox.w);
					break;
				}
			}

		}

		enemySpawnTime.reset();
	}
}

void Game::moveEnemies() {

	for (int i = 0; i < enemyCount; i++) {

		if (enemies[i].isAlive) {
			enemies[i].move(&road, player.velY);
			enemies[i].killStranded();
		}
	}

	for (int i = 0; i < neutralCount; i++) {

		if (neutrals[i].isAlive) {
			neutrals[i].move(&road, player.velY);
			neutrals[i].killStranded();
		}
	}
}

void Game::addPlayerLives() {
	 
	player.setLives(points / PlayerAddLivesThreshold);

}

void Game::countPoints() {

	if (!penaltyTime.isPaused() && penaltyTime.getTime() < penaltyDuration) {

		return;
	}

	if (!penaltyTime.isPaused() && penaltyTime.getTime() > penaltyDuration) {

		penaltyTime.reset();
		penaltyTime.stop();
	}

	if (SDL_HasIntersection(&player.sprite.hitBox, &road.roadTop.hitBox) || SDL_HasIntersection(&player.sprite.hitBox, &road.roadBottom.hitBox)) {
		
		points++;
	}
}

void Game::playerInvincibilityCounter() {

	if (playTime.getTime() >= PlayerInvincibilityTime) {

		player.disableInvincibility();

	}

}

void Game::checkBulletCollision() {

	for (int i = 0; i < bulletCount; i++) {

		for (int j = 0; j < enemyCount; j++) {

			if (SDL_HasIntersection(&player.gun.bullets[i].sprite.hitBox, &enemies[j].sprite.hitBox)) {
				
				if (enemies[j].isAlive) {

					enemies[j].kill();
					points += 1000;
					break;

				}
				printf("\n");
			}

		}

	}

	for (int i = 0; i < bulletCount; i++) {

		for (int j = 0; j < neutralCount; j++) {

			if (SDL_HasIntersection(&player.gun.bullets[i].sprite.hitBox, &neutrals[j].sprite.hitBox)) {

				penaltyTime.reset();
				neutrals[i].kill();
				penaltyTime.start();

			}

		}

	}
}

void Game::moveSprites() {

	moveEnemies();
	player.move();
	road.scrollRoad(player.velY);

}

void Game::changeRoad() {

	if (roadChangeTime.getTime() > 5 + rand() % 3) {

		road.changeRoad();
		roadChangeTime.reset();

	}

}

void Game::handlePlayerEnemyCollisions() {

	for (int i = 0; i < enemyCount; i++) {

		if (SDL_HasIntersection(&enemies[i].sprite.hitBox, &player.sprite.hitBox)) {

			player.destroyCar();
			player.reset();

		}

	}

	for (int i = 0; i < neutralCount; i++) {

		if (SDL_HasIntersection(&neutrals[i].sprite.hitBox, &player.sprite.hitBox)) {

			player.destroyCar();
			player.reset();

		}

	}

}

void Game::isPlayerAlive() {

	if (player.isDead()) {

		isRunning = false;

	}

}

void Game::attackPlayer() {

	for (int i = 0; i < enemyCount; i++) {

		enemies[i].attack(player.sprite.hitBox.x, player.sprite.hitBox.y);

	}

}

void Game::checkPlayerOutOfBounds() {

	if (player.sprite.hitBox.x > PlayRangeEnd || player.sprite.hitBox.x < PlayRangeStart) {

		player.destroyCar();
		player.reset();

	}

}

void Game::countTime() {

	playTime.count();
	enemySpawnTime.count();
	roadChangeTime.count();
	penaltyTime.count();

}

double Game::getPlayTime() {

	return playTime.getTime();

}

void Game::pause() {

	isPaused = true;
	playTime.stop();
	roadChangeTime.stop();
	enemySpawnTime.stop();
	penaltyTime.stop();

}

void Game::unPause() {

	isPaused = false;
	playTime.start();
	roadChangeTime.start();
	enemySpawnTime.start();
	penaltyTime.start();

}

void Game::run(const Uint8* keyState) {

	player.handleEvent(keyState);
	addPlayerLives();
	spawnEnemies();
	handlePlayerEnemyCollisions();
	changeRoad();
	moveSprites();
	countPoints();
	isPlayerAlive();
	checkPlayerOutOfBounds();
	checkBulletCollision();
	playerInvincibilityCounter();
	attackPlayer();

}

void Game::end() {

	quit = true;
	isPaused = false;
	isRunning = false;

}

void Game::restart() {

	points = 0;
	isRunning = true;

	player.respawn();
	road.reset();

	playTime.reset();
	enemySpawnTime.reset();
	roadChangeTime.reset();
	penaltyTime.reset();

	for (int i = 0; i < enemyCount; i++) {

		enemies[i].kill();

	}

	for (int i = 0; i < neutralCount; i++) {

		neutrals[i].kill();
	}

}

