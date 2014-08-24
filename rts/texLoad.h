#pragma once

#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library#include "Output.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
enum GLTexType { NEAREST, LINEAR, MIPMAP };

class texLoad {

public:
	static AUX_RGBImageRec* LoadBMP(char *Filename); 
	static GLuint LoadGLTextures(string bitmap, GLuint texture, GLTexType type = NEAREST);
private:
	
	
};