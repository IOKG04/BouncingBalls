#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "inp.h"
#include "screen_stuff.h"
#include "vec2.h"
#include "ball.h"
#include "constants.h"

void buffer_malloc_error_check();

int columns, rows, curr_size = 1;
char *buffer;
ball_collection *balls;

int main(int argc, char **argv){
    init_collection(&balls);

    addb_collection(balls, (ball){'#', 3, (vec2){3, 3}, (vec2){10, 0}});
    addb_collection(balls, (ball){'*', 5, (vec2){50, 15}, (vec2){-45, -12.5}});
    addb_collection(balls, (ball){'+', 1, (vec2){90, 50}, (vec2){GRAVITY.y, 30}});

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
