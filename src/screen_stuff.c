#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "screen_stuff.h"

// stolen from ChatGPT
struct termios original_tty;

// disables terminal echo
void disable_echo(){
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    original_tty = tty;
    tty.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
// enables terminal echo and flushes stdin
void enable_echo(){
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tty);
    tcflush(STDIN_FILENO, TCIFLUSH);
}

// gets current terminal size in character rows/columns
void get_terminal_size(int *rows, int *cols){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
}
