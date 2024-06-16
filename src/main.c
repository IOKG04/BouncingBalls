#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

int main(int argc, char **argv){
    Display *display = XOpenDisplay(NULL);
    if(display == NULL){
	fprintf(stderr, "Error opening display (%s, %i)\n", __FILE__, __LINE__);
	exit(1);
    }

    printf("Press <Esc> to exit\n");
    char keys[32];
    do{
	XQueryKeymap(display, keys);
	for(int i = 0; i < 32; ++i){
	    for(int j = 0; j < 8; ++j){
		printf("%i", (keys[i] >> j) & 1);
	    }
	}
	printf("\n");
	usleep(500);
    } while(!(keys[1] & 0b10));

    XCloseDisplay(display);
    exit(0);
}
