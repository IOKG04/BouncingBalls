#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "inp.h"
#include "screen_stuff.h"


int main(int argc, char **argv){
    while(1){
	int r, c;
	get_terminal_size(&r, &c);
	printf("%i, %i\n", r, c);
	usleep(500000);
    }

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

