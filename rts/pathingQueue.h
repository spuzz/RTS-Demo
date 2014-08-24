#pragma once

#include <vector>
#include <deque>
#include "point2d.h"
#include "unit.h";
#include "aStar.h"
#include <QTime>
#include "playerControl.h"

using namespace std;

/* Provides a callback mechanism for pathfinding allowing spread of load over multiple frames */

class pathingQueue {

public:
	// Constructors
	pathingQueue();
	//~pathingQueue();

	// Methods
	void addPath(unit* u,playerControl* control);
	void workPathing();
private:

	// Variables
	int availableTime; // Total time per frame available for pathing
	deque<unit*>* paths;
	deque<playerControl*>* pathPlayerControl;

	// Methods

};