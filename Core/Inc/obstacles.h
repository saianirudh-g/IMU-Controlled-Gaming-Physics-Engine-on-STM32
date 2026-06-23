#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "physics.h"

#define NUM_OBS 4

extern Obstacle g_obstacles[NUM_OBS];

void Obstacles_Init(void);
void Obstacles_Update(float dt, float speed);
int  Obstacles_CheckCollision(const Body *b);

#endif
