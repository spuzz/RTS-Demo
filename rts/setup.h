#include <windows.h>		// Header File For Windows - has structures for BMP format
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include "bmp.h"
#include <string>
#include "grid.h"

using namespace std;

class setup {

private:
	grid* mainGrid;
public:
	setup();
	setup(string);
	void createGrid(string);
	void build();
	grid* getGrid() {return mainGrid;}
};