#pragma once

#include "sprite.h"

using namespace std;
class group {

public:

	// Constructors
	group();

	// Main Methods
	bool contains(vector<sprite*> sprs);
	static bool NeedsRemoval(const sprite* spr);
	void steer();
	point2d* collisionAvoidance(sprite* unit);
	point2d* calculateNormal(sprite* collided, point2d* sp, point2d* ep);
	point2d* intersection(point2d* p1, point2d* p2, point2d* p3, point2d* p4);
	point2d* avoidance(int x0, int y0, int x1, int y1, point2d move, point2d* size, int unitId, sprite* unit);
	bool checkCollisionDirection(sprite* colSpr,sprite* unit);

	// Setters and Getters
	sprite* getLeader() { return leader; }
	point2d* getTarget() { return target; }

	vector<sprite*>* getUnits() { return units;  }

	void setLeader(sprite* l) { leader = l; }
	void setUnits(vector<sprite*> selected);
	void setTarget(point2d* t) { target = t; }
private:

	// Methods

	// Variables
	sprite* leader;
	vector<int> removeArray;
	vector<sprite*>* units;
	point2d* target;
	float currentDistanceHolder;
	
};