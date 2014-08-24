#pragma once

#include "logging.h"
#include <string>
#include <vector>
#include "point2d.h"
#include <map>
#include "tile.h"
#include "rectangle.h"

using namespace std;
enum chunkPosition { NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST , OTHER, NONE};
enum direction { NORTH, EAST, SOUTH, WEST, dNORTH_EAST, dNORTH_WEST, dSOUTH_EAST, dSOUTH_WEST };
class quadTreeNode {

public:
	// Constructor
	quadTreeNode(float w, quadTreeNode* p, point2d* location, chunkPosition pos, int lvl);

	// Destructor
	~quadTreeNode() {};

	// Public methods
	void divide(vector<point2d> position,vector<point2d*> sizes);
	bool detectObstacle(vector<point2d> position,vector<point2d*> sizes, vector<quadTreeNode*>* qtc,vector<vector<tile*>>* t);
	bool hasChildren() { return divided; }
	bool isMovable() { return movable; }
	void determineNeighbours();
	static void createMap();
	void determineCollisions(vector<point2d> position,vector<point2d*> sizes);
	void setUpChildrenVector() { quadTreeChildren = new vector<quadTreeNode*>(); }
	bool checkForDivision(point2d position,point2d* size, float widthTest);
	vector<quadTreeNode*>* getChildrenVector() { return quadTreeChildren; }
	point2d* getMidPoint();
	map<chunkPosition,quadTreeNode*> getChildren() { return children; }
	vector<quadTreeNode*>* getNeighbours() { return neighbours; }
	vector<point2d*>* getNeighbourCollisions() { return neighbourCollisions; }
	quadTreeNode* getParent() { return parent; }
	point2d* getLocation() { return location; }
	float getWidth() { return width; }
	
	
private:
	float width;
	int level;
	point2d* location;
	bool divided;
	bool movable;
	chunkPosition gridPosition;
	vector<vector<tile*>>* terrain;
	quadTreeNode* parent;
	map<chunkPosition,quadTreeNode*> children;

	vector<point2d*>* neighbourCollisions;
	vector<quadTreeNode*>* quadTreeChildren;
	vector<quadTreeNode*>* neighbours;
	// Private methods
	bool contains(vector<point2d> position,vector<point2d*> sizes);
	bool checkCurrentTiles(vector<point2d*> tiles,point2d* p1);
	vector<point2d*> checkTiles(rectangle spr);
};