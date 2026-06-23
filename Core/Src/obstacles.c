#include "obstacles.h"
#include <stdlib.h>

Obstacle g_obstacles[NUM_OBS];

void Obstacles_Init(void)
{
    float startX = 0.8f;
    for (int i = 0; i < NUM_OBS; i++)
    {
        g_obstacles[i].x = startX + i * 0.6f;
        g_obstacles[i].y = ((rand() % 100) / 100.0f) * 1.6f - 0.8f;
        g_obstacles[i].w = 0.2f;
        g_obstacles[i].h = 0.2f + ((rand() % 100) / 100.0f) * 0.5f;
    }
}

void Obstacles_Update(float dt, float speed)
{
    for (int i = 0; i < NUM_OBS; i++)
    {
        g_obstacles[i].x -= speed * dt;
        if (g_obstacles[i].x < -1.2f)
        {
            g_obstacles[i].x = 1.2f;
            g_obstacles[i].y = ((rand() % 100) / 100.0f) * 1.6f - 0.8f;
            g_obstacles[i].h = 0.2f + ((rand() % 100) / 100.0f) * 0.5f;
        }
    }
}

int Obstacles_CheckCollision(const Body *b)
{
    for (int i = 0; i < NUM_OBS; i++)
    {
        if (b->pos.x > g_obstacles[i].x - g_obstacles[i].w/2 &&
            b->pos.x < g_obstacles[i].x + g_obstacles[i].w/2 &&
            b->pos.y > g_obstacles[i].y - g_obstacles[i].h/2 &&
            b->pos.y < g_obstacles[i].y + g_obstacles[i].h/2)
        {
            return 1;
        }
    }
    return 0;
}
