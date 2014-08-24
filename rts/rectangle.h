#pragma once
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "texLoad.h"


using namespace std;

/* contains infomation about a rectangle area on the map */

class rectangle {

public:
	//constructors
	rectangle();
	rectangle(point2d* s, point2d* e);
	

	//main methods

	bool isOverLap(rectangle rect);
	bool isUnder(rectangle rect);
	//setters and getters
	void setStartPoint(point2d* s) {start = s; }
	void setEndPoint(point2d* e) {end = e; }
	void setPoints(point2d* s,point2d* e) {start = s, end=e; }
	
	point2d* getStartPoint() {return start; }
	point2d* getEndPoint() {return end; }


private:
	
	point2d* start;
	point2d* end;
};