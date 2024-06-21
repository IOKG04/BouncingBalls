#ifndef SCREEN_STUFF_H__
#define SCREEN_STUFF_H__

// disables terminal echo
void disable_echo();
// enables terminal echo and flushes stdin
void enable_echo();

// gets current terminal size in character rows/columns
void get_terminal_size(int *columns, int *rows);

#endif
