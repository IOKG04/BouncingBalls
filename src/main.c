#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "inp.h"

void disable_echo();
void enable_echo();

int main(int argc, char **argv){
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
    exit(0);
}

// stolen from ChatGPT
struct termios original_tty;
void disable_echo(){
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    original_tty = tty;
    tty.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
void enable_echo(){
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tty);
    tcflush(STDIN_FILENO, TCIFLUSH);
}
