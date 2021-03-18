#include <stdio.h>	// std funcs
#include <X11/Xlib.h>   // Xlib funcs
#include <string.h>     // strlen()
#include <unistd.h>     // sleep()

int main() {
	/*
		example code to create a property in X
		1. first create a Window
		2. create the Atoms that represnts the NAME and TYPE of the property
		3. set value to the property
	*/
	
	// property name / name of the Atom that indicates NAME of the property
	char * name_of_prop = "MESSAGE";
	char * type_of_prop = "STRING";
	// connect to the server	
	Display * xdpy;
	xdpy = XOpenDisplay(NULL);
	if (!xdpy) {
		printf("Couldn't connect to the X Server\n");
		return 1;
	}
	// create an unmapped window (i.e: invisible)
	// to create a window we need a parent window, we are creating a top level window (the first window)
	// so the parent is the Root Window
	
	// the screen number	
  	int screen;

	// Window is a typedef of `unsigned long` windows in X are represnted using IDs
	// these IDs are hex values  
  	Window client_window, root_window;
  	
  	// get the screen number, required to get the root window 
  	// this is a macro not a function
  	// it will extract the screen number we are connected to from the xdpy structure 
	screen = DefaultScreen(xdpy); 
	
	// get the root window, this is also a macro
	root_window = RootWindow(xdpy, screen);
	

	// XCreateSimpleWindow() is a Xlib function used to create a simple window
	// this function requires a parent window, thats the Root Window
	// when we first create a Window in X it will be on `Unmapped` state meaning invisible
	// to map it (make it visible), you have to use XMapWindow(xdpy, client_window) function
	// we won't do that as we dont really need to
	// -----
	// the parameters are just attributes of the window like the x,y, colors ..
	client_window = XCreateSimpleWindow(xdpy, root_window, -10, -10, 1, 1, 0, 0, 0);
	
	// LOG()
	printf("Default screen number:   %d\n", screen);
	printf("Root Window        ID: 0x%lX\n", root_window);
	printf("Window Created     ID: 0x%lX\n", client_window);

	/*
	 	create a property named "MESSAGE"
	*/
	
	
	
	Atom prop_name, prop_type; // NAME and TYPE Atoms
	unsigned char * prop_value = (unsigned char *)"hello world!"; // VALUE
	
	// create NAME Atom
	prop_name = XInternAtom(xdpy, name_of_prop, False);
	if (prop_name == None) {
		printf("failed to create the NAME Atom\n");
		return 1;
   	}
   	
   	// get the STRING Atom, this Atom is predefined
	prop_type = XInternAtom(xdpy, type_of_prop, False);
	if (prop_name == None) {
   	       printf("failed to create the TYPE Atom\n");
		return 1;
	}
	
	// LOG()
	printf("Atom \"%s\" created, ID: %ld\n", name_of_prop, prop_name);
	printf("Atom \"%s\" predefined, ID: %ld\n", type_of_prop, prop_type);
	
	
	// to fill the property with the data we want, we have to use the XChangeProperty() function in the replace mode
	// NOTE: return value "1" in Xlib indicates success :P
	int returned;
	
	returned = XChangeProperty(xdpy,   	/* the connection to the X server */ 	                            					client_window,  /* the window we want to change its property */
                             	prop_name,  	/* NAME */
                             	prop_type,	/* TYPE */
                             	8,         	/* VALUE is an array of `unsigned char` so we use `8` (bits). `16` for `unsigned shor` and `32` for `unsigned int` */
                           	PropModeReplace, /* mode: Replace */
                            	prop_value, 	 /* VALUE */
                            	strlen((char *)prop_value) /* length of VALUE */ 
                            );
                           
	// Flush the output buffer
	XFlush(xdpy);
	
        printf("property created: %d\n", returned);
        printf("\n\n");
        printf("Sleeping, run \"xprop -id 0x%lx\" to see the prop value \n", client_window);  
        
        // sleep cz if we exit the property will be unset   
	for (;;) 
		sleep(1000);
		
	return 0;
}
