#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <vector>
#include <string>
#include "collisionGridNode.h"
#include "playerControl.h"


// Main quadtree used for collision detection and pathfinding
class collisionGrid {

public:

	// Constructors
	collisionGrid(int width, int height);

	// Main public methods
	void reset();
	void addPlayerSprites(playerControl* pc);
	void removeSpriteInTile(sprite* spr);
	void addSpriteToTile(sprite* spr);
	vector<sprite*> getSpritesInTile(int x, int y) { return tree[x]->at(y)->getContainedSprites(); }
	void PrintGrid();

	// Setters and Getters
	vector<vector<collisionGridNode*>*> getTree() { return tree; }


private:
	vector<vector<collisionGridNode*>*> tree;

};