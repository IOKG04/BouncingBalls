#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include "inp.h"

Display *display;
char keys[32], keys_last[32];

// initializes the input reader
int initialize_inp(){
    display = XOpenDisplay(NULL);
    if(display == NULL){
	fprintf(stderr, "Error: failed to open display at %s, %i\n", __FILE__, __LINE__ - 2);
	return 1;
    }
    return 0;
}
//closes the input reader
int close_inp(){
    XCloseDisplay(display);
    return 0;
}
// tests which keys are pressed and returns an array of pressed keys
char *test_keys(){
    if(display == NULL){
	fprintf(stderr, "Error: Display not initialized at %s, %i\n", __FILE__, __LINE__ - 1);
	return NULL;
    }
    memcpy(keys_last, keys, 32);
    XQueryKeymap(display, keys);
    return keys;
}

// returns if the key [keycode] is pressed
int is_pressed_key(int keycode){
    int a = keycode % 8;
    int b = keycode / 8;
    return (keys[b] >> a) & 1;
}
// returns if the key [keycode] was is pressed for the first test
int is_pressed_down(int keycode){
    int a = keycode % 8;
    int b = keycode / 8;
    return ((keys[b] >> a) & 1) & !((keys_last[b] >> a) & 1);
}
