#include "aStar.h"
#include "collision.h"
#include "utilFuncs.h"
#include "control.h"

using namespace std;
/* Main path finding class using A* search algorithm. */
aStar::aStar(point2d* trgt, point2d startLoc, point2d* sze, int id, bool useCollision) {
	control* ctrl = control::getInstance();
	quadTree* qdTree = ctrl->getQuadTree();
	target = qdTree->determineLocation(trgt,true);
	startLocation = qdTree->determineLocation(new point2d(startLoc.getX() + sze->getX()/200,startLoc.getY()  + sze->getY()/200),true);
	size = sze;
	unitId = id;
	totalTime = 0;
	debugTime = 0;
	unitCollision = useCollision;
	calculatePath();
	
}

/* overall function for determining the path */
void aStar::calculatePath() {
	logging::log(logging::FINEST,"Pathing Started");
	QTime timer;
	timer.start();
	startOpenList();
	while(!collision::pointToRectCollision(target->getMidPoint(),calcCurNodeRectBox(currentNode))) {
		// If openList has 0 size without reaching point then it is unreachable
		if(unitCollision == true) {
			if(closedList.size() > 5) {
				break;
			}
		}
		if(openList.size() == 0) {
			std::map<pair<float,float>,aStarNode*>::const_iterator it;
			int key = -1;
			int hScoreTest = 0;
			for (it = closedList.begin(); it != closedList.end(); ++it)
			{
				if (it->second->getHVal() < hScoreTest || hScoreTest == 0)
				{
					hScoreTest = it->second->getHVal();
					currentNode == it->second;
				}
			}
			break;
		}
		findNextNode();
	}
	if(closedList.size() !=0) {
		retrievePathFromClosed();
	}
	
	stringstream ss;
	ss << "Total pathing time taken = " << timer.elapsed();
	ss << " Total Length = " << finalPath.size();
	ss << endl;
	ss << " Total Collision Time = " << debugTime;
	logging::log(logging::INFO,ss.str());
	logging::log(logging::FINEST,"Pathing FINISHED");
}

/* calculate a rect using the current node and the sprite creating this paths size.
   This is used to detect a collision with the target location */
rectangle aStar::calcCurNodeRectBox(aStarNode* node) {
	quadTreeNode* tmpChild = node->getQdNode();
	point2d* childLoc = tmpChild->getLocation();
	rectangle rect(new point2d(childLoc->getX(),childLoc->getY()),new point2d(childLoc->getX() + tmpChild->getWidth(),childLoc->getY() + tmpChild->getWidth())); 
	return rect;
}

/* starts the path calculation by adding the start location and running the algorithm on this,
   In a different function as it does some initial configs with start node */
void aStar::startOpenList() {
	currentNode = new aStarNode(startLocation,target->getMidPoint(),size);
	currentNode->setGVal(0);
	quadTreeNode* tmpChild = currentNode->getQdNode();
	point2d* childLoc = tmpChild->getLocation();
	currentNode->setHVal(currentNode->calculateHScore(target->getMidPoint()));
	currentNode->setParent(NULL);
	if(collision::pointToRectCollision(target->getMidPoint(),calcCurNodeRectBox(currentNode))) {
		logging::log(logging::BASIC,"UNIT ALREADY AT TARGET");
		return;
	}
	pair<float,float> key(currentNode->getLocation()->getX(),currentNode->getLocation()->getY());
	closedList.insert(make_pair(key,currentNode));
	totalNodes = 1;
	addOpenListNodes(currentNode);
}

/* Calculate the F (total) value of all current open list nodes and
   determine which has the lowest score then remove use this as the next
   node to look at */
void aStar::findNextNode() {
	float fVal = 0;
	for(int a=0;a<openList.size();a++) {
		if(fVal == 0 | openList[a]->getFVal() < fVal) {
			currentNode = openList[a];
			fVal = currentNode->getFVal();
		}
		
	}
	utilFuncs::erase(&openList,currentNode);

	pair<float,float> key(currentNode->getLocation()->getX(),currentNode->getLocation()->getY());
	closedList.insert(make_pair(key,currentNode));

	addOpenListNodes(currentNode);


}


/* Once the target node has been added to the list the loop is finished.
   To determine the best path we take the parent of the target node when it
   was added and recursively look through the parent nodes added each one
   to the path until we find the start location. */
void aStar::retrievePathFromClosed() {
	vector<aStarNode*> reversedPath;
	aStarNode* pathPointer = currentNode;
	reversedPath.push_back(pathPointer);
	while(pathPointer->getParent() != NULL) {
		pathPointer = pathPointer->getParent();
		reversedPath.push_back(pathPointer);
	}
	// reverse the path so that it goes from start to finish
	if(reversedPath.size() > 0) {
		for(int a=reversedPath.size() - 2;a >= 0;a--) {
			finalPath.push_back(reversedPath[a]);
		}
	}
	//cout<<"ASTAR PATH"<<endl;
	//for(int a=0; a<finalPath.size();a++) {
	//	cout<<finalPath[a]->getLocation()->getX()<<" "<<finalPath[a]->getLocation()->getY()<<endl;
	//}
	// Smooth path!
	//finalPath = pathSmooth(finalPath);
}

/* Function for checking if a node is already in either the open or closed list. */
aStarNode* aStar::checkInList(aStarNode* node,vector<aStarNode*>* list) {


	float xLoc = node->getLocation()->getX();
	float yLoc = node->getLocation()->getY();
	for(int a=0;a<list->size();a++) {
		
		if(list->at(a)->getLocation()->getX() == xLoc) {
			if(list->at(a)->getLocation()->getY() == yLoc) {
				return list->at(a);
			}
		}
		
	}

	return NULL;
}

/* Calculation and check function. Takes the newest node added to the closed list
   and added any new adjacent tiles to the open list after calculating all the values
   for these new nodes using the current tile as the parent */
void aStar::addOpenListNodes(aStarNode* node) {
	QTime timer;
	timer.start();
	aStarNode* newPoint;
	point2d* pos;
	bool diagonal = false;

	// Cycle through adjacent tile vector. Again there is probably a better way of doing this.
	for(int a=0;a<node->getNeighbours()->size();a++) {
		if(unitCollision == true) {
			if(raytrace(node->getLocation()->getX(),node->getLocation()->getY(),
				node->getNeighbours()->at(a)->getLocation()->getX(),node->getNeighbours()->at(a)->getLocation()->getY())) 
			{
				continue;
			}
				
		}
		newPoint = new aStarNode(node->getNeighbours()->at(a),target->getMidPoint(),size);

		if(collision::pointToRectCollision(target->getMidPoint(),calcCurNodeRectBox(newPoint))) {
			newPoint->setParent(node);
			currentNode = newPoint;
			pair<float,float> key(currentNode->getLocation()->getX(),currentNode->getLocation()->getY());
			closedList.insert(make_pair(key,currentNode));
			return;
		}
		
		// Check if it is in either list
		
		aStarNode* nodeOpenTest = checkInList(newPoint,&openList);
		
		std::map<pair<float,float>,aStarNode*>::const_iterator it;
		aStarNode* nodeClosedTest = NULL;
		int startTime = timer.elapsed();
		it = closedList.find(make_pair(newPoint->getLocation()->getX(),newPoint->getLocation()->getY()));
		if(it != closedList.end()) {
			nodeClosedTest = it->second;
		}
		debugTime += (timer.elapsed() - startTime);
		if(nodeOpenTest == NULL && nodeClosedTest == NULL) {;
			// If it is in neither list and doesn't collide with any unit, building or unmovable tile then add.
			//if(!collision::pathCollision(newPoint->getLocation(),size,unitId)) {
				newPoint->setHVal(newPoint->calculateHScore(target->getMidPoint()));
				newPoint->setGVal(newPoint->calculateGScore(node,diagonal));
				newPoint->calculateFScore();

				newPoint->setParent(node);
				openList.push_back(newPoint);
				totalNodes += 1;
			//}
		}
		else if(nodeClosedTest == NULL) {
			/* if it is in the open list then check if it is quicker to go through this new parent tile and if
			   it is then change the tiles parent to this one */
			if(newPoint->calculateGScore(node,diagonal) < nodeOpenTest->getGVal()) {
				nodeOpenTest->setParent(node);
				newPoint->setGVal(newPoint->calculateGScore(node,diagonal));
				nodeOpenTest->calculateFScore();
			}
		}
		
	}
}

/* This is the function for the path smoothing so that the unit will move realistically rather than from point to point.
   Ray tracing is used to determine if points along the path can be skipped */
  
vector<aStarNode*> aStar::pathSmooth(vector<aStarNode*> path) {
	int currentSmoothTest = 1;
	vector<aStarNode*> smoothedPath;
	aStarNode* tmpPoint1;
	aStarNode* tmpPoint2;
	while(currentSmoothTest < path.size()) {
		// Initial point to first path point
		if(smoothedPath.size() == 0) {
			tmpPoint2 = path.at(currentSmoothTest);
			if(raytrace(floor(startLocation->getLocation()->getX()),floor(startLocation->getLocation()->getY()),
				floor(tmpPoint2->getLocation()->getX()),floor(tmpPoint2->getLocation()->getY())) == true) {
					smoothedPath.push_back(path.at(currentSmoothTest - 1));
			}
			currentSmoothTest += 1;
		}
		else {
			tmpPoint1 = smoothedPath.at(smoothedPath.size() - 1);
			tmpPoint2 = path.at(currentSmoothTest);
			if(raytrace(floor(tmpPoint1->getLocation()->getX()),floor(tmpPoint1->getLocation()->getY()),
				floor(tmpPoint2->getLocation()->getX()),floor(tmpPoint2->getLocation()->getY())) == true) {
					smoothedPath.push_back(path.at(currentSmoothTest - 1));
			}
			currentSmoothTest += 1;
		}
	}
	return smoothedPath;
}

/* ray tracing algorithm to determine if there is line of sight between 2 points */
bool aStar::raytrace(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0;
    int y = y0;
    int n = 1 + dx + dy;
    int x_inc = (x1 > x0) ? 1 : -1;
    int y_inc = (y1 > y0) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;
	control* ctrl = control::getInstance();
	vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
    for (; n > 0; --n)
    {
		if(grd->at(y).at(x)->getMovable() == 0) {
			return true;
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(x,y);
		if(sprsInTile.size() != 0) {
			
			for(int a=0;a<sprsInTile.size();a++){
				if(sprsInTile.at(a)->getMovable() == false) {
					return true;
				}
			}
			
		}
        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }
	return false;
}



