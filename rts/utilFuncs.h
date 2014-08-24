#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "rectangle.h"
#include "sprite.h"
#include "aStarNode.h"


class utilFuncs {

public:
	static std::vector<sprite*>* erase(std::vector<sprite*>* myNumbers_in, sprite* number_in);
	static std::vector<aStarNode*>* erase(std::vector<aStarNode*>* myNumbers_in, aStarNode* number_in);
	static float manhattenDistance(float p1x, float p1y, float p2x, float p2y);
	static float manhattenDistance(point2d p1, point2d p2);
private:

};