#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "aStarNode.h"
#include "rectangle.h"
#include "binaryHeap.h"
#include "quadTreeNode.h"


class aStar {

public:
	// constructors
	aStar(point2d* trgt, point2d startLoc, point2d* size, int id, bool useCollision = false);

	// main methods
	void calculatePath();
	void startOpenList();
	void findNextNode();
	rectangle calcCurNodeRectBox(aStarNode* node);
	void addOpenListNodes(aStarNode* node);
	aStarNode* checkInList(aStarNode* node,vector<aStarNode*>* list);
	void retrievePathFromClosed();
	bool raytrace(int x0, int y0, int x1, int y1);
	vector<aStarNode*> aStar::pathSmooth(vector<aStarNode*> path);


	// setters and getters
	vector<aStarNode*> getFinalPath() { return finalPath; }

private:
	quadTreeNode* target;
	point2d* size;
	int unitId;
	float speed;
	quadTreeNode* startLocation;
	aStarNode* currentNode;
	vector<aStarNode*> openList;
	map<pair<float,float>,aStarNode*> closedList;
	vector<point2d*> adjacent;
	vector<aStarNode*> finalPath;
	bool unitCollision;

	// testing stuff
	int totalNodes;
	int totalTime;
	int debugTime;

};