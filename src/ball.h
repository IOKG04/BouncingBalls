#ifndef BALL_H__
#define BALL_H__

#include <stddef.h>
#include "vec2.h"

// balls :3
typedef struct{
    char   visual;
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
void base_step_ball(ball *b, double width, double height);

// ball collection
typedef struct{
    size_t  amount, max_amount;
    ball   *balls;
} ball_collection;

// initializes a collection
int init_collection(ball_collection **bc);
// frees a collection
void free_collection(ball_collection *bc);
// adds a ball to a collection
void addb_collection(ball_collection *bc, ball b);
// removes a ball from a collection
void removeb_collection(ball_collection *bc, int index);

// applies base_step_ball() to all balls in a collection
void base_step_collection(ball_collection *bc, double width, double height);
// renderes all balls in a collection
void render_collection(ball_collection *bc, char *buffer, double width, double height);

// prints info about all balls in a collection to stdout
void print_info_collection(ball_collection *bc);

#endif
