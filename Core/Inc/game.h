#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "physics.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_GAMEOVER
} GameState;

extern GameState g_gameState;

void Game_Init(void);
void Game_Update(float dt);

#endif
