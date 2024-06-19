#ifndef BALL_H__
#define BALL_H__

#include "vec2.h"

// balls :3
typedef struct{
    double radius;
    vec2   position,
	   velocity;
} ball;

// returns squared radius of a ball
double squared_radius_ball(ball b);
// returns if a point lies inside a ball
int inside_ball(ball b, vec2 vec);
// renderes a ball onto a buffer
void render_ball(ball b, char *buffer, int width, int height);

// applies a balls velocity and gravity
void base_step_ball(ball *b);

#endif
