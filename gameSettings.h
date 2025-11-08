#pragma once

#define DEBUG_MODE					true

#define TARGET_MS_PER_FRAME			30
#define GAME_WINDOW_SIZE            768

#define LEVEL_TILE_COUNT			16
#define LEVEL_TILE_SIZE				GAME_WINDOW_SIZE / LEVEL_TILE_COUNT

class SETTINGS {
public:
	inline static bool SHOW_COLLIDERS = false;
	inline static int SHOW_COLLIDER_MODE = 0;
};