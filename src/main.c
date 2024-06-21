#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "inp.h"
#include "screen_stuff.h"
#include "vec2.h"
#include "ball.h"
#include "constants.h"

#define RANDOM_DOUBLE (rand() / (double)RAND_MAX)
#define RANDOM_DOUBLE_SIGNED (RANDOM_DOUBLE * 2 - 1)

void buffer_malloc_error_check();

int columns, rows, curr_size = 1;
char *buffer;
ball_collection *balls;

int main(int argc, char **argv){
    srand(time(NULL));

    init_collection(&balls);

    printf("\n%i\n", __LINE__);

    buffer = malloc(1);
    buffer_malloc_error_check();

    int inp_err_code = initialize_inp();
    if(inp_err_code != 0){
	fprintf(stderr, "Error: %i at %s, %i\n", inp_err_code, __FILE__, __LINE__ - 2);
	exit(inp_err_code);
    }

    disable_echo();
    printf("\x1b[2J");
    do{
	get_terminal_size(&columns, &rows);
	columns -= 2;
	rows -= 4;
	if(rows * columns > curr_size){
	    free(buffer);
	    buffer = malloc(rows * columns);
	    buffer_malloc_error_check();
	    curr_size = rows * columns;
	}

	test_keys();

	if(is_pressed_down(SPAWN_KEY)){
	    double nb_radius = RANDOM_DOUBLE * (RANDOM_RADIUS_MAX - RANDOM_RADIUS_MIN) + RANDOM_RADIUS_MIN;
	    vec2 nb_offset = (vec2){RANDOM_DOUBLE_SIGNED * RANDOM_OFFSET_MAX.x + columns * .5, RANDOM_DOUBLE_SIGNED * RANDOM_OFFSET_MAX.y + rows * .5};
	    vec2 nb_velocity = (vec2){RANDOM_DOUBLE_SIGNED * RANDOM_VELOCITY_MAX.x, RANDOM_DOUBLE_SIGNED * RANDOM_VELOCITY_MAX.y};
	    addb_collection(balls, (ball){'#', nb_radius, nb_offset, nb_velocity});
	}

	base_step_collection(balls, columns, rows * 2);

	memset(buffer, ' ', columns * rows);
        render_collection(balls, buffer, columns, rows);

	printf("\x1b[d");
        for(int i = 0; i < columns * rows; ++i){
	    if(i % columns == 0) putchar('|');
	    putchar(buffer[i]);
	    if(i % columns == columns - 1) printf("|\n");
        }
	putchar('+'); for(int i = 0; i < columns; ++i) putchar('='); printf("+\n");

	print_info_collection(balls);
	putchar('\n');

	usleep(STEP_DELAY);
    } while(!is_pressed_key(EXIT_KEY));
    enable_echo();

    free(buffer);
    close_inp();
    free_collection(balls);
    exit(0);
}

inline void buffer_malloc_error_check(){
    if(buffer == NULL){
	fprintf(stderr, "Error: Buffer allocation went wrong, please help\n");
	exit(1);
    }
}
