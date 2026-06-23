#ifndef RENDERER_H
#define RENDERER_H

#include "physics.h"
#include "particles.h"
#include <stdint.h>

void Renderer_Init(void);
void Renderer_DrawMenu(uint32_t highScore);
void Renderer_DrawGame(const Body *ball,
                       const Obstacle *obsArr,
                       int score,
                       uint32_t highScore,
                       int gameOver,
                       const Particle *particles,
                       int particleCount);
void Renderer_DrawGameOver(int score, uint32_t highScore, int newHighScore);

#endif
