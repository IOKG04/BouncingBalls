#include "vec2.h"

#include "ball.h"

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
	int y = (int)b.position.y;
	if(x >= 0 && x < width &&
	   y >= 0 && y < height)
	    buffer[x + y * width] = '*';
	return;
    }

    // normal case
    int x_start = (int)(b.position.x - b.radius) - 1;
    int x_end = (int)(b.position.x + b.radius) + 1;
    int y_start = (int)(b.position.y - b.radius) - 1;
    int y_end = (int)(b.position.y + b.radius) + 1;
#define SET_MIN_MAX(d, m) d = d < 0 ? 0 : (d >= m ? m - 1 : d)
    SET_MIN_MAX(x_start, width);
    SET_MIN_MAX(x_end, width);
    SET_MIN_MAX(y_start, height);
    SET_MIN_MAX(y_end, height);
#undef SET_MIN_MAX
    for(int x = x_start; x <= x_end; ++x){
	for(int y = y_start; y <= y_end; ++y){
	    vec2 ppos = {x, y};
	    if(inside_ball(b, ppos)){
		buffer[x % width + y * width] = '*';
	    }
	}
    }
}
