#include "pathingQueue.h"
pathingQueue::pathingQueue() {
	availableTime = 70;
	paths = new deque<unit*>();
	pathPlayerControl = new deque<playerControl*>();
}

void pathingQueue::addPath(unit* spr,playerControl* control) {
	bool inQueue = false;
	for(int a=0;a<paths->size();a++) {
		if(paths->at(a) == spr) {
			inQueue = true;
			
		}
	}
	if(inQueue == false) {
		paths->push_back(spr);
		pathPlayerControl->push_back(control);
	}
}

void pathingQueue::workPathing() {
	unit* tmpUnit;
	playerControl* tmpControl;
	QTime timer;
	timer.start();
	// Limits the amount of time this frame for running path finding
	while(timer.elapsed() < 40 && paths->size() > 0) {
		
		tmpUnit = paths->front();
		tmpControl = pathPlayerControl->front();
		tmpControl->updateGroupPath(tmpUnit,new aStar(tmpUnit->getTarget(),tmpUnit->getPosition(),tmpUnit->getSize(),tmpUnit->getUnitId()));
		paths->pop_front();
		pathPlayerControl->pop_front();
	}
	
}