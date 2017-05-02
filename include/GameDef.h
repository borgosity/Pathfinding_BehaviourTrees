#pragma once

#include <math.h>

#define M_PI       3.14159265358979323846   // pi

const int SCREEN_W = 1280;
const int SCREEN_H = 720;

const int HALF_SW = SCREEN_W >> 1;
const int HALF_SH = SCREEN_H >> 1;


// variables for things in the world
const float		PLAYER_SIZE			= 10.0f;
const float		PLAYER_EDGE			= PLAYER_SIZE / 2.0f;
const float		PLAYER_START_X		= 1000.0f;
const float		PLAYER_START_Y		= 100.0f;
const float		PLAYER_MAX_SPEED	= 2.0f;
const float		PLAYER_MAX_ACCEL	= 0.5f;
const float		PLAYER_MAX_FORCE	= 0.1f;
const float		PLAYER_EVADE_RANGE	= 60.0f;
const float		PLAYER_ARRIVAL_DIS	= 50.0f;
const float		PLAYER_SLOW_DIS		= 100.0f;

const int		WANDERER_COUNT = 20;
const float		WANDERER_FOLLOW_RANGE = 50;
const int		WANDERER_GROUP = 3;

const int		OBSTACLE_COUNT = 30;

const float		WANDER_RADIUS	= 50.0f;
const float		WANDER_JITTER	= 0.25f;
const float		WANDER_DISTANCE = (float)(rand() % 75 + 1);

const float		NODE_DISTANCE = 40;
const float		NODE_COST_WND = 100;

const float		BASE_POS_X	= PLAYER_START_X + 40;
const float		BASE_POS_Y	= PLAYER_START_Y - 40;
const float		BASE_SIZE	= 120;

const float		ROCKET_POS_X	= 60;
const float		ROCKET_POS_Y	= 660;
const float		ROCKET_SIZE		= 120;

// variables for the game
const float SIZE_BONUS = 1;
const float SIZE_PENALTY = -2;