#pragma once

#include "point2d.h"
#include "texLoad.h"
#include "ability.h"
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include <map>
#include "qbasictimer.h"

using namespace std;

class ability {

public:
	//constructors
	ability();
	ability(string image, string name);

	//main methods
	virtual void use();
	static ability* create(string type,string image,map<string,string> attr);

	//getters and setters
	string getImage() { return image; }

	void setImage(string i) { image = i; }

protected:
	string image;
	string name;

};