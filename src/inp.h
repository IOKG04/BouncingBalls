#ifndef INP_H__
#define INP_H__

// keycodes for important keys
#define EXIT_KEY  9
#define SPAWN_KEY 65

// initializes the input reader
int initialize_inp();
// closes the input reader
int close_inp();
// tests which keys are pressed and returns an array of pressed keys
char *test_keys();

// returns if the key [keycode] is pressed
int is_pressed_key(int keycode);
// returns if the key [keycode] was is pressed for the first test
int is_pressed_down(int keycode);

#endif
