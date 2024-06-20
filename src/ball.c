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
    if(b.radius < 1){
	int x = (int)b.position.x;
	int y = (int)(b.position.y / 2);
	if(x >= 0 && x < width &&
	   y >= 0 && y < height)
	    buffer[x + y * width] = '*';
	return;
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
		buffer[x % width + y * width] = '*';
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
	b->velocity.x = -b->velocity.x;
    }
    else if(b->position.x + b->radius > width){
	b->position.x = 2 * width - 2 * b->radius - b->position.x;
	b->velocity.x = -b->velocity.x;
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
	    double new_velocity = -(b->velocity.y + GRAVITY.y * t_impact);
	    b->position.y = height - b->radius;
	    b->velocity.y = new_velocity + GRAVITY.y * (DELTA_TIME / 2 - t_impact) / 2;
	    b->position.y += b->velocity.y * (DELTA_TIME - t_impact);
	}

	/*b->position.y = 2 * height - 2 * b->radius - b->position.y;
	b->velocity.y = -b->velocity.y;*/
    }
}
