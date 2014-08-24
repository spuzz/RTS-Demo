#include "quadTree.h"
#include "rectangle.h"

#define EPSILON 0.0001   // Define your own tolerance.
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

quadTree::quadTree(vector<point2d> position,vector<point2d*> sizes,vector<vector<tile*>>* terrain, int mapSize) {
	// Setup initial node tree that is the size of the map
	mainQuadTree = new quadTreeNode(mapSize, NULL, new point2d(0,0),NONE,0);
	// Start breaking down the quadTree by detecting any obstacles in the initial node
	mainQuadTree->setUpChildrenVector();
	mainQuadTree->createMap();
	mainQuadTree->detectObstacle(position,sizes,mainQuadTree->getChildrenVector(),terrain);
	logging::log(logging::BASIC,"TOTAL CHILDREN");
	logging::log(logging::BASIC,(float)mainQuadTree->getChildrenVector()->size());
	for(int a=0;a<mainQuadTree->getChildrenVector()->size();a++) {
		mainQuadTree->getChildrenVector()->at(a)->determineNeighbours();
	}
}

quadTreeNode* quadTree::getClosest(point2d* point) {
	float distance = -1;
	quadTreeNode* tmp;
	for(int a=0;a<mainQuadTree->getChildrenVector()->size();a++) {
		quadTreeNode* tmpChild = mainQuadTree->getChildrenVector()->at(a);
		point2d* childLoc = tmpChild->getLocation();
		if(abs(childLoc->getX() - point->getX()) + abs(childLoc->getY() - point->getY()) < distance || distance == -1){
			tmp = tmpChild;
			distance = abs(childLoc->getX() - point->getX()) + abs(childLoc->getY() - point->getY());
		}
	}
	return tmp;
}

quadTreeNode* quadTree::determineLocation(point2d* point,boolean closest) {
	for(int a=0;a<mainQuadTree->getChildrenVector()->size();a++) {
		quadTreeNode* tmpChild = mainQuadTree->getChildrenVector()->at(a);
		point2d* childLoc = tmpChild->getLocation();

		rectangle tmpOne(new point2d(childLoc->getX(),childLoc->getY()),new point2d(childLoc->getX() + tmpChild->getWidth(),childLoc->getY() + tmpChild->getWidth())); 
		if(pointToRectCollision(point,tmpOne)) 
		{
			return tmpChild;
		}
	}
	if(closest == true) {
		return getClosest(point);
	}
	return NULL;
}

bool quadTree::pointToRectCollision(point2d* point, rectangle rect) {
	if((point->getX() >= rect.getStartPoint()->getX() || FLOAT_EQ(point->getX(),rect.getStartPoint()->getX())) && 
		(point->getX() <= rect.getEndPoint()->getX()|| FLOAT_EQ(point->getX(),rect.getEndPoint()->getX())) && 
		(point->getY() >= rect.getStartPoint()->getY() || FLOAT_EQ(point->getY(),rect.getStartPoint()->getY())) && 
		(point->getY() <= rect.getEndPoint()->getY() || FLOAT_EQ(point->getY(),rect.getEndPoint()->getY())))
	{
		return true;
	}
	return false;
}