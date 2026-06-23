#include "physics.h"

void Physics_Update(Body *b, float dt)
{
    b->vel.x += b->acc.x * dt;
    b->vel.y += b->acc.y * dt;

    b->pos.x += b->vel.x * dt;
    b->pos.y += b->vel.y * dt;

    if (b->pos.x < WORLD_MIN_X) {
        b->pos.x = WORLD_MIN_X;
        b->vel.x = -b->vel.x * BOUNCE_FACTOR;
    }
    if (b->pos.x > WORLD_MAX_X) {
        b->pos.x = WORLD_MAX_X;
        b->vel.x = -b->vel.x * BOUNCE_FACTOR;
    }
    if (b->pos.y < WORLD_MIN_Y) {
        b->pos.y = WORLD_MIN_Y;
        b->vel.y = -b->vel.y * BOUNCE_FACTOR;
    }
    if (b->pos.y > WORLD_MAX_Y) {
        b->pos.y = WORLD_MAX_Y;
        b->vel.y = -b->vel.y * BOUNCE_FACTOR;
    }

    b->vel.x *= 0.99f;
    b->vel.y *= 0.99f;
}
