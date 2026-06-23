#include "particles.h"
#include <stdlib.h>
#include <math.h>

Particle g_particles[MAX_PARTICLES];

void Particles_Init(void)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
        g_particles[i].active = 0;
}

void Particles_SpawnExplosion(float x, float y)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        g_particles[i].active = 1;
        g_particles[i].life   = 1.0f;

        float angle = (rand() % 628) / 100.0f;
        float speed = 0.5f + (rand() % 100) / 100.0f;

        g_particles[i].pos.x = x;
        g_particles[i].pos.y = y;

        g_particles[i].vel.x = cosf(angle) * speed;
        g_particles[i].vel.y = sinf(angle) * speed;
    }
}

void Particles_SpawnDust(float x, float y)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!g_particles[i].active)
        {
            g_particles[i].active = 1;
            g_particles[i].life   = 0.3f;

            g_particles[i].pos.x = x;
            g_particles[i].pos.y = y;

            g_particles[i].vel.x = ((rand() % 100) / 500.0f) - 0.1f;
            g_particles[i].vel.y = ((rand() % 100) / 500.0f) - 0.1f;
            break;
        }
    }
}

void Particles_Update(float dt)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!g_particles[i].active)
            continue;

        g_particles[i].life -= dt;
        if (g_particles[i].life <= 0.0f)
        {
            g_particles[i].active = 0;
            continue;
        }

        g_particles[i].pos.x += g_particles[i].vel.x * dt;
        g_particles[i].pos.y += g_particles[i].vel.y * dt;

        g_particles[i].vel.x *= 0.95f;
        g_particles[i].vel.y *= 0.95f;
    }
}
