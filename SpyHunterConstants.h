#pragma once
#include "Rgb.h"

const colorRGB green = { 150, 0, 0 };
const colorRGB black = { 0, 0, 0 };
const colorRGB grey = { 150, 150, 150 };

const int ScreenWidth = 1024;
const int ScreenHeight = 768;

const int roadWideWidth = 520;
const int roadNarrowWidth = 260;
const int roadNormalWidth = 350;
const int roadHeight = 800;

const double maxVelY = 10;
const double maxVelX = 4;
const double maxAcc = 0.2;

const int enemyCount = 4;
const int neutralCount = 2;
const int bulletCount = 4;

const int PlayRangeStart = 100;
const int PlayRangeEnd = ScreenWidth - 100;
const int PlayerInvincibilityTime = 20;
const int PlayerAddLivesThreshold = 20000;

const int penaltyDuration = 2;

const char PlayerCarPath[] = "./images/PlayerCar.bmp";
const char EnemyCarPath[] = "./images/EnemyCar.bmp";
const char NeutralCarPath[] = "./images/NeutralCar.bmp";

const char charSetPath[] = "./images/cs8x8.bmp";
const char roadPath[] = "./images/road.bmp";
const char roadWidePath[] = "./images/roadWide.bmp";
const char roadNarrowPath[] = "./images/roadNarrow.bmp";
const char bulletPath[] = "./images/bullet.bmp";

const int maxBufferSize = 32;