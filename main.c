#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

#include "../../arg.h"

char *argv0;
static Display *dpy;
static Window root;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-t]\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	int di;
	unsigned int dui, tflag;
	Window win, dw;
	XEvent ev;

	argv0 = argv[0] ;
	tflag = 0 ;

	ARGBEGIN {
	case 't' :
		tflag = 1 ;
	break;
	default:
		usage();
	} ARGEND

	if(! (dpy = XOpenDisplay(0)) ){
		fprintf(stderr, "%s: cannot open display\n");
		exit(1);
	}

	root = RootWindow(dpy, DefaultScreen(dpy)) ;
	
	if(tflag){
		if(XGrabPointer(dpy, root, False,
				ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
				GrabModeAsync, GrabModeAsync,
				None, None, CurrentTime) != GrabSuccess){
			fprintf(stderr, "%s: cannot grab pointer\n", argv0);
			exit(1);
		}
		do{
			XMaskEvent(dpy, ButtonPressMask|ButtonReleaseMask, &ev);
		}while( ev.type != ButtonPress);
	}
	XQueryPointer(dpy, root, &dw, &win, &di, &di, &di, &di, &dui );
	printf("%d\n", win);
	
	return 0 ;
}
