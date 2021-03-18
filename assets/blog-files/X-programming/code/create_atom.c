// compile with "-lX11" flag to link the Xlib files
// gcc file.c -o file -lX11
#include <stdio.h> 	// std functions
#include <X11/Xlib.h>   // Xlib functions make sure you installed the dev package

int main() {
	/*
		This example we will create an Atom named "ATOMX11"
	*/	
	// Display structure is serving the connection to the X Server, it is holding the file discriptor of the network socket, display number, ..
	Display * xdpy; 	
	// Atom is just a typedef of `unsigned long` (basically represnts the IDs we talked about)
	Atom created_atom; 	
	// Atom name
	char * atom_name = "ATOMX11";	
	// connect to the X Server
	xdpy = XOpenDisplay(NULL);
	
	// Xlib function to create Atoms: XInterntom(display_connection, "Name of Atom", OnlyIfExist)
	// 
	// OnlyIfExist flag is used whe we need an Atom we are expecting to be created
	// in this case we are not, we are the ones who will create "ATOMX11" Atom
	// so we set it to False
	created_atom = XInternAtom(xdpy, atom_name, False);
	if (created_atom == None)
		printf("failed to create Atom");
	// we use XGetAtomName() to get the atom name
	// XGetAtomName(connection, atom)
	char * obtianed_atom_name;
	obtianed_atom_name = XGetAtomName(xdpy, created_atom);
	// LOG()
	printf("Atom \"%s\" is created, ID: %ld\n", atom_name, created_atom);
	printf("Atom name we got using XGetAtomName() for Atom %ld -> \"%s\"\n", created_atom, obtianed_atom_name);
	return 0;
}
