#ifndef PARTICLES_H
#define PARTICLES_H

#include "physics.h"

#define MAX_PARTICLES 60

typedef struct {
    Vec2  pos;
    Vec2  vel;
    float life;
    int   active;
} Particle;

extern Particle g_particles[MAX_PARTICLES];

void Particles_Init(void);
void Particles_Update(float dt);
void Particles_SpawnExplosion(float x, float y);
void Particles_SpawnDust(float x, float y);

#endif
