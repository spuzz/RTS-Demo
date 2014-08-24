#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "quadTreeNode.h"
#include <QTime>

class aStarNode {

public:
	// constructors
	aStarNode(quadTreeNode* n, point2d* target, point2d* size);

	// main methods
	void calculateFScore();
	float calculateHScore(point2d* target);
	float calculateGScore(aStarNode* testParent,bool diagonal);
	bool compare(aStarNode* node);

	// setters and getters
	vector<quadTreeNode*>* getNeighbours() { return node->getNeighbours(); }
	point2d* getLocation() { return node->getMidPoint(); }
	aStarNode* getParent() { return parent; }
	quadTreeNode* getQdNode() { return node; }
	float getFVal() { return F; }
	float getGVal() { return G; }
	float getHVal() { return H; }

	void setParent(aStarNode* node) { parent = node; }
	void setFVal(float val) { F = val; }
	void setGVal(float val) { G = val; }
	void setHVal(float val) { H = val; }


	friend bool operator== (aStarNode &cP1, aStarNode &cP2)
	{
		if(*cP1.getLocation() == *cP2.getLocation()) {
			return true;
		} else {
			return false;
		}
	}



private:
	aStarNode* parent;
	quadTreeNode* node;
	float F,G,H;
	float speed;
};

