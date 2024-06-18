#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "inp.h"
#include "screen_stuff.h"
#include "vec2.h"
#include "ball.h"


int main(int argc, char **argv){
    char buffer[256];
    memset(buffer, ' ', 256);
    ball b = {3, {4, 4}};
    ball c = {3, {4, 11.5}};
    ball d = {1, {9, 7}};
    render_ball(b, buffer, 16, 16);
    render_ball(c, buffer, 16, 16);
    render_ball(d, buffer, 16, 16);
    for(int i = 0; i < 256; ++i){
	putchar(buffer[i]);
	if(i % 16 == 15) putchar('\n');
    }

    /*
    vec2 a = {3, 4};
    double l = length_vec2(a);
    vec2 b = normalized_vec2(a);
    vec2 c = {2, 3};
    a = cross_vec2(a, c);
    a = cross_div_vec2(a, c);
    printf("%lf, {%lf, %lf}, {%lf, %lf}\n", l, b.x, b.y, a.x, a.y);
    */

    /*
    int inp_err_code = initialize_inp();
    if(inp_err_code != 0){
	fprintf(stderr, "Error: %i at %s, %i\n", inp_err_code, __FILE__, __LINE__ - 2);
	exit(inp_err_code);
    }

    disable_echo();
    do{
	test_keys();
	printf("%i %i\n", is_pressed_key(SPAWN_KEY), is_pressed_down(SPAWN_KEY));
	usleep(500000);
    } while(!is_pressed_key(EXIT_KEY));
    enable_echo();

    close_inp();
    */

    exit(0);
}

