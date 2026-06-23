#ifndef PHYSICS_H
#define PHYSICS_H
// World boundaries
#define WORLD_MIN_X   -1.0f
#define WORLD_MAX_X    1.0f
#define WORLD_MIN_Y   -1.0f
#define WORLD_MAX_Y    1.0f
// Physics constants
#define BOUNCE_FACTOR  0.8f

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
} Body;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} Obstacle;

void Physics_Update(Body *b, float dt);

#endif
