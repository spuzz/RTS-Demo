#include "aStarNode.h"

aStarNode::aStarNode(quadTreeNode* n, point2d* target,point2d* size) {
	node = n;
	H = 0;
	G = 0;
	F = 0;
	calculateHScore(target);
}

/* Simple function adding current traversal distance score from start point
   and the heuristic distance to target point */
void aStarNode::calculateFScore() {

	F = G + H;
}

/* Heuristic distance score from this node to path final target,
   base on Manhatten distance calculation for estimating the distance
   from this point to target */
float aStarNode::calculateHScore(point2d* target) {
	float hScore = 0;
	// x Distance to target location
	hScore += (abs(target->getX() - getLocation()->getX()));

	// y Distance to target location
	hScore += (abs(target->getY() - getLocation()->getY()));
	return hScore;
}

float aStarNode::calculateGScore(aStarNode* testParent, bool diagonal) {
	float gScore = 0;
	gScore = testParent->getGVal() +  (abs(testParent->getLocation()->getX() - getLocation()->getX()))
		+  (abs(testParent->getLocation()->getY() - getLocation()->getY()));
	return gScore;
}

/* Simple function to determine if a pointer node is the same as this one */
bool aStarNode::compare(aStarNode* node2) {
	if(node2->getLocation()->getX() == getLocation()->getX() &&
		node2->getLocation()->getY() == getLocation()->getY()) {
		return true;
	} else {
		return false;
	}
}

