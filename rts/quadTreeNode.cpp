#include "quadTreeNode.h"
#include "rectangle.h"
#include "collision.h"

static float minSize = 0.5;
static int OUT_LEFT = 1;
static int OUT_TOP = 2;
static int OUT_RIGHT = 4;
static int OUT_BOTTOM = 8;

static map<chunkPosition,map<direction,chunkPosition>*> directionNeighbour;
static vector<direction>* directions;

quadTreeNode::quadTreeNode(float w, quadTreeNode* p, point2d* loc, chunkPosition pos, int lvl) {
	// NOTE: since all nodes are squares width == height. BAD NAME
	width = w;
	level = lvl;
	divided = false;
	movable = false;
	// map location of this node
	location = loc;
	// The large node that was divided into this and 3 other nodes
	parent = p;

	gridPosition = pos;

}

/* This function takes all player contollers and uses information on all relevant buildings (which includes terrain)
   and determines if this node contains any of them. */
bool quadTreeNode::detectObstacle(vector<point2d> position,vector<point2d*> sizes, vector<quadTreeNode*>* qtc, vector<vector<tile*>>* t) {
	quadTreeChildren = qtc;
	terrain = t;
	bool containCheck = false;
	// This is messy code but does the job. Goes through each player controller and determines if any of the buildings
	// are contained in the node
	rectangle tileRect(new point2d((int)location->getX(),(int)location->getY()),new point2d((int)(location->getX()+(width*1.5) - 0.01),(int)(location->getY()+(width*1.5) - 0.01)));
	vector<point2d*> tmpTiles = checkTiles(tileRect);
	// after calculating tiles, determine if each of these tiles is traversable
	for(int a=0;a<tmpTiles.size();a++) {
		// main control singleton access to tile grid

		if(terrain->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
			if(width/2 >= minSize) {
				divide(position,sizes);
				return true;
			}
			else {
				rectangle tileRect(new point2d((int)location->getX(),(int)location->getY()),new point2d((int)(location->getX()+(width) - 0.01),(int)(location->getY()+(width) - 0.01)));
				vector<point2d*> tmpTiles = checkTiles(tileRect);
				// after calculating tiles, determine if each of these tiles is traversable
				for(int a=0;a<tmpTiles.size();a++) {
					if(terrain->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
						return true;
					}
				}
				
			}
		}
	}
	if(contains(position,sizes)) {
		return true;
	}
	movable = true;
	determineCollisions(position,sizes);
	quadTreeChildren->push_back(this);
	return false;
}

/* function for comparing building and node bounding boxes to determine if the node needs to be divided */
bool quadTreeNode::contains(vector<point2d> position,vector<point2d*> sizes) {
	for(int a=0;a<position.size();a++) {
		if(checkForDivision(position[a],sizes[a],1.5) == true) {
		//if((position[a].getX() > location->getX() && position[a].getX() < location->getX() + width)
		//	|| (position[a].getX() + sizes[a]->getX()/100 > location->getX() && position[a].getX()  + sizes[a]->getX()/100 < location->getX() + width)
		//	|| (position[a].getX() <= location->getX() && position[a].getX()  + sizes[a]->getX()/100 >= location->getX() + width)
		//){
		//	if((position[a].getY() > location->getY() && position[a].getY() < location->getY() + width) 
		//		|| (position[a].getY() + sizes[a]->getY()/100 > location->getY() && position[a].getY()  + sizes[a]->getY()/100 < location->getY() + width)
		//		|| (position[a].getY() <= location->getY() && position[a].getY()  + sizes[a]->getY()/100 >= location->getY() + width)
		//	){
				// Check if this node has been divided the maximum amount before dividing again
				// NOTE: value currently static, possibly a better way to use so its easy to update
				if(width/2 >= minSize) {
					divide(position,sizes);

					return true;
				}
				else {
					if(checkForDivision(position[a],sizes[a],1) == true) {
						return true;
					}
				}
			//}
		}
	}
	return false;
}

bool quadTreeNode::checkForDivision(point2d position,point2d* size, float widthTest) {
		if((position.getX() > location->getX() - width*(widthTest-1) && position.getX() < location->getX() + width*widthTest)
			|| (position.getX() + size->getX()/100 > location->getX() - width*(widthTest-1) && position.getX()  + size->getX()/100 < location->getX() + width*widthTest)
			|| (position.getX() <= location->getX() && position.getX()  - width*(widthTest-1)  + size->getX()/100 >= location->getX() + width*widthTest)
		){
			if((position.getY() > location->getY() - width*(widthTest-1) && position.getY() < location->getY() + width*widthTest) 
				|| (position.getY() + size->getY()/100 > location->getY() - width*(widthTest-1) && position.getY()  + size->getY()/100 < location->getY() + width*widthTest)
				|| (position.getY() <= location->getY() && position.getY() - width*(widthTest-1)  + size->getY()/100 >= location->getY() + width*widthTest)
			){
				return true;
			}
		}
		return false;
}

/* Recursive function that calls divides the node and starts the detection check again on all of these */
void quadTreeNode::divide(vector<point2d> position,vector<point2d*> sizes) {
	divided = true;
	movable = true;
	// NOTE: Again messy code but simple to understand. Consider rewriting to make clearer.
	children[NORTH_WEST] = new quadTreeNode(width/2,this,new point2d(location->getX(),location->getY()),NORTH_WEST, level + 1);
	children[NORTH_EAST] = new quadTreeNode(width/2,this,new point2d(location->getX() +width/2,location->getY()),NORTH_EAST, level + 1);
	children[SOUTH_WEST] = new quadTreeNode(width/2,this,new point2d(location->getX(),location->getY()+width/2),SOUTH_WEST, level + 1);
	children[SOUTH_EAST] = new quadTreeNode(width/2,this,new point2d(location->getX() +width/2,location->getY()+width/2),SOUTH_EAST, level + 1);
	children[NORTH_WEST]->detectObstacle(position,sizes,quadTreeChildren,terrain);
	children[NORTH_EAST]->detectObstacle(position,sizes,quadTreeChildren,terrain);
	children[SOUTH_WEST]->detectObstacle(position,sizes,quadTreeChildren,terrain);
	children[SOUTH_EAST]->detectObstacle(position,sizes,quadTreeChildren,terrain);

}
point2d* quadTreeNode::getMidPoint() {
	point2d* tmp = new point2d(getLocation()->getX() + width/2,getLocation()->getY()+width/2);
	return tmp;
}

void quadTreeNode::determineCollisions(vector<point2d> position,vector<point2d*> sizes) {
	point2d* expandedLoc = new point2d(location->getX() -0.5,location->getY() - 0.5);
	float expandedWidth = width + 1;
	neighbourCollisions = new vector<point2d*>();
	rectangle tileRect(new point2d((int)expandedLoc->getX(),(int)expandedLoc->getY()),new point2d((int)(expandedLoc->getX()+ expandedWidth - 0.01),(int)(expandedLoc->getY()+expandedWidth - 0.01)));
	vector<point2d*> tmpTiles = checkTiles(tileRect);
	// after calculating tiles, determine if each of these tiles is traversable
	for(int a=0;a<tmpTiles.size();a++) {
		// main control singleton access to tile grid

		if(terrain->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
			neighbourCollisions->push_back(&terrain->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getPosition());

		}
	}
	for(int a=0;a<position.size();a++) {
		if((position[a].getX() > expandedLoc->getX() && position[a].getX() < expandedLoc->getX() + expandedWidth)
			|| (position[a].getX() + sizes[a]->getX()/100 > expandedLoc->getX() && position[a].getX()  + sizes[a]->getX()/100 < expandedLoc->getX() + expandedWidth)
			|| (position[a].getX() <= expandedLoc->getX() && position[a].getX()  + sizes[a]->getX()/100 >= expandedLoc->getX() + expandedWidth)
		){
			if((position[a].getY() > expandedLoc->getY() && position[a].getY() < expandedLoc->getY() + expandedWidth) 
				|| (position[a].getY() + sizes[a]->getY()/100 > expandedLoc->getY() && position[a].getY()  + sizes[a]->getY()/100 < expandedLoc->getY() + expandedWidth)
				|| (position[a].getY() <= expandedLoc->getY() && position[a].getY()  + sizes[a]->getY()/100 >= expandedLoc->getY() + expandedWidth)
			){
				neighbourCollisions->push_back(&position[a]);
			}
		}
	}
}

void quadTreeNode::determineNeighbours() {
	neighbours = new vector<quadTreeNode*>();
	rectangle* tmpOne;
	rectangle* tmpTwo;
	tmpOne = new rectangle(new point2d(location->getX() - minSize,location->getY() - minSize),new point2d(location->getX() + width + minSize,location->getY() + width + minSize)); 
	for(int a=0;a<quadTreeChildren->size();a++) {
		bool badNeighbour = false;
		bool diagonal = true;
		quadTreeNode* tmpChild = quadTreeChildren->at(a);
		point2d* childLoc = tmpChild->getLocation();
		rectangle tmpTwo(new point2d(childLoc->getX(),childLoc->getY()),new point2d(childLoc->getX() + tmpChild->getWidth(),childLoc->getY() + tmpChild->getWidth())); 
		if(tmpOne->isOverLap(tmpTwo)) {
			if(abs(tmpChild->getMidPoint()->getX() - getMidPoint()->getX()) != abs(tmpChild->getMidPoint()->getY() - getMidPoint()->getY())) {
				diagonal = false;
			}
			if(diagonal == true) {
				for(int b=0;b<neighbourCollisions->size();b++) {
					for(int c=0;c<tmpChild->getNeighbourCollisions()->size();c++) {
						if(neighbourCollisions->at(b)->compare(tmpChild->getNeighbourCollisions()->at(c))) {
							badNeighbour = true;
						}
					}
				}
				if(badNeighbour == false) {
					neighbours->push_back(tmpChild);
				}
			}
			else {
				neighbours->push_back(tmpChild);
			}

		}
	}
		
}


void quadTreeNode::createMap() {
	// NOTE: currently have no better idea how to implement this
	
	direction a[] = {NORTH,EAST,SOUTH,WEST,dNORTH_WEST,dNORTH_EAST,dSOUTH_EAST,dSOUTH_WEST};
	directions = new vector<direction>(a,a+8);

	map<direction,chunkPosition>* tmp = new map<direction,chunkPosition>();
	tmp->insert(pair<direction,chunkPosition>(NORTH,OTHER));
	tmp->insert(pair<direction,chunkPosition>(NORTH,OTHER));
	tmp->insert(pair<direction,chunkPosition>(EAST,NORTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(SOUTH,SOUTH_WEST));
	tmp->insert(pair<direction,chunkPosition>(WEST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_WEST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_EAST,SOUTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_WEST,OTHER));
	directionNeighbour[NORTH_WEST] = tmp;

	tmp = new map<direction,chunkPosition>();
	tmp->insert(pair<direction,chunkPosition>(NORTH,OTHER));
	tmp->insert(pair<direction,chunkPosition>(EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(SOUTH,SOUTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(WEST,NORTH_WEST));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_WEST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_WEST,SOUTH_WEST));
	directionNeighbour[NORTH_EAST] = tmp;

	tmp = new map<direction,chunkPosition>();
	tmp->insert(pair<direction,chunkPosition>(NORTH,NORTH_WEST));
	tmp->insert(pair<direction,chunkPosition>(EAST,SOUTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(SOUTH,OTHER));
	tmp->insert(pair<direction,chunkPosition>(WEST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_WEST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_EAST,NORTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_WEST,OTHER));
	directionNeighbour[SOUTH_WEST] = tmp;

	tmp = new map<direction,chunkPosition>();
	tmp->insert(pair<direction,chunkPosition>(NORTH,NORTH_EAST));
	tmp->insert(pair<direction,chunkPosition>(EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(SOUTH,OTHER));
	tmp->insert(pair<direction,chunkPosition>(WEST,SOUTH_WEST));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_WEST,NORTH_WEST));
	tmp->insert(pair<direction,chunkPosition>(dNORTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_EAST,OTHER));
	tmp->insert(pair<direction,chunkPosition>(dSOUTH_WEST,OTHER));
	directionNeighbour[SOUTH_EAST] = tmp;

}

bool quadTreeNode::checkCurrentTiles(vector<point2d*> tiles,point2d* p1) {
	for(int a=0;a<tiles.size();a++) {
		if(tiles[a]->compare(p1)) {
			return true;
		}
	}
	return false;
}

vector<point2d*> quadTreeNode::checkTiles(rectangle spr) {
	vector<point2d*> tiles;
	bool result = false;
	point2d* tmp;
	for(int a=spr.getStartPoint()->getX();a<=spr.getEndPoint()->getX();a++) {
		for(int b=spr.getStartPoint()->getY();b<=spr.getEndPoint()->getY();b++) {
			if(a < 64 && a >= 0 && b < 64 && b >= 0) {
				tiles.push_back(new point2d(a,b));
			}
			
		}
	}
	return tiles;
}