#pragma once

#include "playerControl.h"
#include "logging.h"
#include <string>
#include <vector>
#include "quadTreeNode.h"

using namespace std;

/* Quad Tree class for path finding around buildings and terrain features (e.g. trees)*/
class quadTree {

public:
	// Constructors
	quadTree(vector<point2d> position,vector<point2d*> sizes,vector<vector<tile*>>* terrain, int mapSize);

	// Destructors
	~quadTree() {}

	// Public methods
	quadTreeNode* quadTree::getClosest(point2d* point);
	quadTreeNode* determineLocation(point2d* point,boolean closest = false);
	quadTreeNode* getMainQuadTreeNode() { return mainQuadTree; }
	bool pointToRectCollision(point2d* point, rectangle rect);

private:
	/* Node of quad tree that is the whole map which will be divided down. This division
	is done within each node */
	quadTreeNode* mainQuadTree;
};