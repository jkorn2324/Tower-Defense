#pragma once

#pragma region game_parameters

#define WINDOW_NAME "Tower Defense Game"
#define DEBUG_MODE false

const unsigned int WINDOW_SIZE_X = 1024;
const unsigned int WINDOW_SIZE_Y = 768;
const unsigned int WAIT_TIME_TICKS = 16;
const bool DISPLAY_LOGS = true;

#pragma endregion

#pragma region tilesheet_parameters

const unsigned int TILESHEET_SIZE_X = 2944;
const unsigned int TILESHEET_SIZE_Y = 1664;
const unsigned int TILES_PER_COLUMN = 13;
const unsigned int TILES_PER_ROW = 23;
const unsigned int TILE_SIZE_X = 64;
const unsigned int TILE_SIZE_Y = 64;

#define TILESHEET_PATH "Assets/Sprites/towerDefense_tilesheet.png"

#pragma endregion