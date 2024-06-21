#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vec2.h"
#include "constants.h"

#include "ball.h"

// applies wall collision
void wall_collisions_ball(ball *b, double width, double height);

// returns squared radius of a ball
double squared_radius_ball(ball b){
    return b.radius * b.radius;
}
// returns if a point lies inside a ball
int inside_ball(ball b, vec2 vec){
    vec2 rel = subtract_vec2(vec, b.position);
    return squared_length_vec2(rel) <= squared_radius_ball(b);
}
// renderes a ball onto a buffer
void render_ball(ball b, char *buffer, int width, int height){
    // special case (don't want em not to show up)
    if(b.radius <= 1){
	int x = (int)b.position.x;
	int y = (int)(b.position.y / 2 + 0.5);
	if(x >= 0 && x < width &&
	   y >= 0 && y < height)
	    buffer[x + y * width] = b.visual;
	//return;
    }

    // normal case
    int x_start = (int)(b.position.x - b.radius) - 1;
    int x_end = (int)(b.position.x + b.radius) + 1;
    int y_start = (int)((b.position.y - b.radius) / 2) - 1;
    int y_end = (int)((b.position.y + b.radius) / 2) + 1;
#define SET_MIN_MAX(d, m) d = d < 0 ? 0 : (d >= m ? m - 1 : d)
    SET_MIN_MAX(x_start, width);
    SET_MIN_MAX(x_end, width);
    SET_MIN_MAX(y_start, height);
    SET_MIN_MAX(y_end, height);
#undef SET_MIN_MAX
    for(int x = x_start; x <= x_end; ++x){
	for(int y = y_start; y <= y_end; ++y){
	    vec2 ppos = {x, y * 2};
	    if(inside_ball(b, ppos)){
		buffer[x % width + y * width] = b.visual;
	    }
	}
    }
}

// applies a balls velocity and gravity
void base_step_ball(ball *b, double width, double height){
    b->velocity = add_vec2(b->velocity, scale_vec2(GRAVITY, .5 * DELTA_TIME));
    b->position = add_vec2(b->position, scale_vec2(b->velocity, DELTA_TIME));
    wall_collisions_ball(b, width, height);
    b->velocity = add_vec2(b->velocity, scale_vec2(GRAVITY, .5 * DELTA_TIME));
}
// applies wall collision
void wall_collisions_ball(ball *b, double width, double height){
    if(b->position.x - b->radius < 0){
	b->position.x = b->radius * 2 - b->position.x;
	b->velocity.x = -b->velocity.x * sqrt(ENERGY_LOSS_FACTOR.x);
    }
    else if(b->position.x + b->radius > width){
	b->position.x = 2 * width - 2 * b->radius - b->position.x;
	b->velocity.x = -b->velocity.x * sqrt(ENERGY_LOSS_FACTOR.x);
    }
    if(b->position.y + b->radius > height){
	// thx chatgpt for this part :3
	b->position.y -= b->velocity.y * DELTA_TIME;
	b->velocity.y -= GRAVITY.y * DELTA_TIME * .5;
	double a_ = 0.5 * GRAVITY.y,
	       b_ = b->velocity.y,
	       c_ = b->position.y + b->radius - height;
	double discriminant = b_ * b_ - 4 * a_ * c_;
	if(discriminant < 0){
	    b->velocity.y += GRAVITY.y * DELTA_TIME * .5;
	    b->position.y += b->velocity.y * DELTA_TIME;
	}
	else{
	    double t_impact = (-b_ + sqrt(discriminant)) / (2 * a_);
	    double new_velocity = -(b->velocity.y + GRAVITY.y * t_impact) * sqrt(ENERGY_LOSS_FACTOR.y);
	    b->position.y = height - b->radius;
	    b->velocity.y = new_velocity + GRAVITY.y * (DELTA_TIME / 2 - t_impact);
	    b->position.y += b->velocity.y * (DELTA_TIME - t_impact);
	}
    }
}

// doubles the capacity of a collection
int double_collection(ball_collection *bc);

// initializes a collection
int init_collection(ball_collection **bc){
    if(*bc != NULL) free_collection(*bc);
    *bc = malloc(sizeof(ball_collection));
    if(*bc == NULL){
	fprintf(stderr, "Error: Something happened while allocating a new ball collection\n");
	return 1;
    }
    (*bc)->balls = malloc(sizeof(ball));
    if((*bc)->balls == NULL){
	fprintf(stderr, "Error: Something happened while allocating a new ball collection's balls\n");
	return 2;
    }
    (*bc)->amount = 0;
    (*bc)->max_amount = 1;
    return 0;
}
// frees a collection
void free_collection(ball_collection *bc){
    free(bc->balls);
    free(bc);
}
// adds a ball to a collection
void addb_collection(ball_collection *bc, ball b){
    if(bc->amount >= bc->max_amount) double_collection(bc);
    bc->balls[bc->amount] = b;
    ++bc->amount;
}
// removes a ball from a collection
void removeb_collection(ball_collection *bc, int index){
    if(index < 0 || index >= bc->amount) return;
    for(int i = index; i < bc->amount - 1; ++i) bc->balls[i] = bc->balls[i + 1];
    --bc->amount;
}

// applies base_step_ball() to all balls in a collection
void base_step_collection(ball_collection *bc, double width, double height){
    for(int i = 0; i < bc->amount; ++i){
	base_step_ball(&bc->balls[i], width, height);
    }
}
// renderes all balls in a collection
void render_collection(ball_collection *bc, char *buffer, double width, double height){
    for(int i = 0; i < bc->amount; ++i){
	render_ball(bc->balls[i], buffer, width, height);
    }
}

// doubles the capacity of a collection
int double_collection(ball_collection *bc){
    ball *new_balls = malloc(bc->max_amount * 2 * sizeof(ball));
    if(new_balls == NULL){
	fprintf(stderr, "Error while reallocating a ball collection\n");
	return 1;
    }
    ball *old_balls = bc->balls;
    bc->balls = new_balls;
    for(int i = 0; i < bc->max_amount; ++i) bc->balls[i] = old_balls[i];
    free(old_balls);

    bc->max_amount *= 2;
    return 0;
}

// prints info about all balls in a collection to stdout
void print_info_collection(ball_collection *bc){
    putchar('{');
    for(int i = 0; i < bc->amount; ++i){
	printf("{{%lf, %lf}, {%lf, %lf}}, ", bc->balls[i].position.x, bc->balls[i].position.y, bc->balls[i].velocity.x, bc->balls[i].velocity.y);
    }
    putchar('}');
}
