#pragma once

#include <windows.h>		// Header File For Windows - has structures for BMP format
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include <string>
#include "control.h"
#include "rectangle.h"


class collision {

public:
	// constructors
	collision();

	// main methods
	static vector<point2d*> testCollision(point2d pos,point2d* size,int damage,int unitId, string colour);
	static sprite* spriteCollision(point2d pos,point2d* size,int damage,int unitId, string colour);
	static bool pathCollision(point2d* pos,point2d* size, int unitId);
	static bool pointToRectCollision(point2d* point, rectangle rect);
	static bool pathFindingTargetCollision(point2d* point, rectangle rect,float speed);
	static vector<point2d*> checkTiles(rectangle spr);

private:
	
	static bool checkCurrentTiles(vector<point2d*> tiles,point2d* p1);

};