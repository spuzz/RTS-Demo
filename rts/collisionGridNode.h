#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <vector>
#include <string>
#include "point2d.h"
#include "sprite.h"


/* quadtree node class, contains information on a tile in the map.
   This information includes sprites that are traveling through this tile
   and any paths that cross through this tile aswell. When one of these 
   nodes adds or loses it cause an update on any sprites with paths through
   this tile */

class collisionGridNode {

public:

	// Constructors
	collisionGridNode(int xPos, int yPos);
	

	// Main Methods
	void clearPoints();

	// Setters and Getters
	void setContainedSprites(vector<sprite*> set) { containedSprites = set; }
	void addSpritePath(sprite* spr);
	void addSprite(sprite* spr);
	void addDeviatedPath(sprite* spr);

	vector<sprite*> getContainedSprites();
	vector<sprite*> getSpritePaths();
	vector<sprite*> getDeviatedPaths();

private:

	// quadtree tile loc
	point2d* treeLoc;
	
	// contains any sprites that are currently moving through this tile
	vector<sprite*> containedSprites;

	// contains any sprites that have a path through this tile
	vector<sprite*> spritePaths;

	// contains any sprites with paths that have been deviated because of sprites in this tile
	vector<sprite*> deviatedPaths;
};