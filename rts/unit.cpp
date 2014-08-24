#include "unit.h"
#include <math.h>
#include "control.h"
#include "rectangle.h"
#include "buildTier.h"
#include "buildAbility.h"
#include "xmlparser.h"
#include "collision.h"
#include "utilFuncs.h"

#define EPSILON 0.0001   // Define your own tolerance.
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

static bool IsOnSegment(double xi, double yi, double xj, double yj,
                        double xk, double yk) {
  return (xi <= xk || xj <= xk) && (xk <= xi || xk <= xj) &&
         (yi <= yk || yj <= yk) && (yk <= yi || yk <= yj);
}

static char ComputeDirection(double xi, double yi, double xj, double yj,
                             double xk, double yk) {
  double a = (xk - xi) * (yj - yi);
  double b = (xj - xi) * (yk - yi);
  return a < b ? -1 : a > b ? 1 : 0;
}

/** Do line segments (x1, y1)--(x2, y2) and (x3, y3)--(x4, y4) intersect? */
bool DoLineSegmentsIntersect(double x1, double y1, double x2, double y2,
                             double x3, double y3, double x4, double y4) {
  char d1 = ComputeDirection(x3, y3, x4, y4, x1, y1);
  char d2 = ComputeDirection(x3, y3, x4, y4, x2, y2);
  char d3 = ComputeDirection(x1, y1, x2, y2, x3, y3);
  char d4 = ComputeDirection(x1, y1, x2, y2, x4, y4);
  return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
          ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
         (d1 == 0 && IsOnSegment(x3, y3, x4, y4, x1, y1)) ||
         (d2 == 0 && IsOnSegment(x3, y3, x4, y4, x2, y2)) ||
         (d3 == 0 && IsOnSegment(x1, y1, x2, y2, x3, y3)) ||
         (d4 == 0 && IsOnSegment(x1, y1, x2, y2, x4, y4));
}

unit::unit() : sprite() {
	health = 0;
	maxHealth = 0;
	damage = 5;
	armor = 0;
	range = 0;
	movementSpeed = 0.5;
	movable = true;
	currentPath = 0;
	vision = 5;
	direction = new point2d(0.5,0.5);
	velocity = new point2d(0,0);
	target = new point2d(-1,-1);
	xPathAdj = 0;
	yPathAdj = 0;
	unitStatus = IDLE;
}

void unit::setup(map<string,string> xmlValues) {

	// use xml values from file to create unit stats
	health = atoi(xmlValues["health"].c_str());
	maxHealth = atoi(xmlValues["health"].c_str());
	damage = atoi(xmlValues["damage"].c_str());
	armor = atoi(xmlValues["armor"].c_str());
	range = atoi(xmlValues["health"].c_str());
	movementSpeed = atof(xmlValues["movespeed"].c_str());
	setSize(atof(xmlValues["sizeX"].c_str()),atof(xmlValues["sizeY"].c_str()));
	//createAbilities(xmlValues);
	updateTiles();
}

void unit::createAbilities(map<string,map<string,string>> xmlValues) {

	for ( map<string,map<string,string>>::const_iterator iter = xmlValues.begin();
		iter != xmlValues.end(); ++iter ) {
			string name = iter->first;
			map<string,string> tmp = iter->second;
			ability* ab = ability::create(iter->first,tmp["image"] + ".png",tmp);
			addAbility(ab);
	}
		

}

string unit::update() {
	if(health <= 0) {
		logging::log(logging::FINE,"A unit has died");
		return "dead";
	}
	
	determineTarget();
	calculateDirection();
	if(!(direction->getX() == 0 && direction->getY() ==0)) {
		probeDirection();
	}
	velocity->setX(movementSpeed*direction->getX());
	velocity->setY(movementSpeed*direction->getY());

	return "alive";

}

bool unit::avoidance(float moveX, float moveY) {
	point2d move(location.getX() + moveX,location.getY() + moveY);
	vector<point2d*> tmpTiles = collision::testCollision(move,getSize(),damage,unitId,colour);
	if(tmpTiles.size() > 0) {
		moveUnit(tmpTiles,move);
		return true;
	}
	else { return false; }
}

void unit::moveUnit(vector<point2d*> ts, point2d move) {
	control* ctrl = control::getInstance();
	setPosition(move.getX(),move.getY());
	for(int a=0;a<ts.size();a++) {
		ctrl->getColTree()->removeSpriteInTile(this);
	}
	tiles = ts;
	ctrl->getColTree()->addSpriteToTile(this);
}

void unit::updateGoal(point2d* tar, bool att) {
	if(att == true) {
		unitStatus = ATTACKMOVE;
	}
	else {
		unitStatus = MOVE;
	}
	setTarget(tar);
	currentPath = 0;
	//path = leader->getPa;
	//pathVector = path->getFinalPath();
	//currentPath = 0;
}

void unit::move() {

	
	point2d move(location.getX() + velocity->getX(),location.getY() + velocity->getY());
	vector<point2d*> tmpTiles = collision::testCollision(move,getSize(),damage,unitId,colour);
	if(tmpTiles.size() > 0) {
		moveUnit(tmpTiles,move);
	}
}



void unit::determineTarget() {
	point2d* closestTar;
	switch(unitStatus) {
	case IDLE:
		closestTar = checkVision();
		if(closestTar->getX() != -1) {
			setTarget(closestTar);
		}
		else {
			setTarget(new point2d(-1,-1));
		}
		break;
	case EXPLORE: 
		setTarget(new point2d(0,0));
		break;
	case MOVE:
		break;
	case ATTACKMOVE:
		closestTar = checkVision();
		if(closestTar->getX() != -1) {
			setTarget(closestTar);
		}
		break;
	case ATTACK:
		break;
	}
}

void unit::updatePath(aStar* completedPath)  { 
	path = completedPath;
	pathVector = path->getFinalPath();
	currentPath = 0;
}

point2d* unit::checkVision() {
	float closest = 0;
	point2d* tar = new point2d(-1,-1);
	control* ctrl = control::getInstance();
	for(int a = (int)location.getX() - vision;a<= (int)location.getX() + vision;a++) {
		for(int b = (int)location.getY() - vision;b<= (int)location.getY() + vision;b++) {
			if(a < 0 || a > 63 || b < 0 || b > 63) {
				continue;
			}
			vector<sprite*> tmp = ctrl->getColTree()->getSpritesInTile(a,b);
			for(int c=0;c<tmp.size();c++) {
				if(tmp[c]->getColour() != getColour() && tmp[c]->getColour() != "grey") {
					if(closest == 0 || 
						(abs(location.getX() - tmp[c]->getPosition().getX()) + 
						abs(location.getY() - tmp[c]->getPosition().getY()) < closest)) {
							tar = new point2d(tmp[c]->getPosition().getX(),tmp[c]->getPosition().getY());
					}
				}

			}
		}
	}
	return tar;
}


void unit::calculateDirection() {

	control* ctrl = control::getInstance();
	point2d childLoc = getPosition();
	point2d* pathPosition;
	// This simply adds a distance modify to determine how far the sprite can be from the target path position to move onto the next.
	float checkDistance = 1;
	
	if(target->getX() == -1) {
		// Checks if no target at all
		setDirection(0,0);
		return;
	}

	if(currentPath == pathVector.size() - 1 || pathVector.size() == 0) {
		//cout<<pathVector[currentPath]->getLocation()->getX()<<" "<<pathVector[currentPath]->getLocation()->getY()<<endl;
		cout<<target->getX()<<" "<<target->getY()<<endl;
		// Checks if this is the final position in the path
		checkDistance = 0.1;
		pathPosition = target;
	}
	else if(currentPath > pathVector.size() - 1) {

		setDirection(0,0);
		if(unitStatus == MOVE || unitStatus == ATTACKMOVE) {
			unitStatus = IDLE;
		}
		return;
	}
	else {
		pathPosition = pathVector[currentPath]->getLocation();
	}
	if(currentPath == 0 && pathVector.size() > 0) {
		//currentPath = pathSmooth(pathVector,-1);
	}
	if(abs(childLoc.getX() - pathPosition->getX()) < 1 && abs(childLoc.getY() - pathPosition->getY()) < 1) {
		currentPath += 1;
		//currentPath = pathSmooth(pathVector,currentPath - 1);
	}
	else {
		float xDir, yDir;
		xDir = ((pathPosition->getX() - (getPosition().getX() + (getSize()->getX()/200))));
		yDir = ((pathPosition->getY() - (getPosition().getY() + (getSize()->getY()/200))));
		float total = abs(xDir) + abs(yDir);
		setDirection(xDir/total,yDir/total);
	}

	


}



int unit::pathSmooth(vector<aStarNode*> path, int current) {
	smooth = true;
	int tmp;
	tmp = current + 2;
	cout<<"START SMOOTHING"<<endl;
	cout<<"PATH SIZE "<<path.size()<<endl;
	point2d loc;
	if(current == -1) {
		loc = getPosition();
	}
	else {
		loc = *path[current]->getLocation();
	}
	while((tmp < path.size())) {
		// REDO THIS YOUR LAZY>>>
		if(raytrace(loc.getX() + size->getX()/200,loc.getY() + size->getY()/200,
			path[tmp]->getLocation()->getX(),path[tmp]->getLocation()->getY())) {
				return tmp - 1;
		}
		if(raytrace(loc.getX()+ size->getX()/200 ,loc.getY() - size->getY()/200,
			path[tmp]->getLocation()->getX(),path[tmp]->getLocation()->getY())) {
				return tmp - 1;
		}
		if(raytrace(loc.getX() - size->getX()/200,loc.getY() + size->getY()/200,
			path[tmp]->getLocation()->getX(),path[tmp]->getLocation()->getY())) {
				return tmp - 1;
		}
		if(raytrace(loc.getX() - size->getX()/200,loc.getY() - size->getY()/200,
			path[tmp]->getLocation()->getX(),path[tmp]->getLocation()->getY())) {
				return tmp - 1;
		}
		tmp += 1;
	}
	return tmp -1;
}

bool unit::raytrace(int x0, int y0, int x1, int y1) {
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

    for (; n > 0; --n)
    {
		control* ctrl = control::getInstance();
		vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
		cout<<"GRID TILE CHECKED "<<x<<" "<<y<<endl;
		if(grd->at(y).at(x)->getMovable() == 0) {
			rayTraceXCollide = x;
			rayTraceYCollide = y;
			return true;
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(x,y);
		if(sprsInTile.size() != 0) {
			for(int a=0;a<sprsInTile.size();a++){
				if(sprsInTile.at(a)->getMovable() == false) {
					rayTraceXCollide = x;
					rayTraceYCollide = y;
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
	rayTraceXCollide = -1;
	rayTraceYCollide = -1;
	return false;
}

// Collision avoidance to smoothly go around corners and avoid other units
void unit::probeDirection() {
	point2d* midPoint = new point2d(location.getX() + (size->getX()/200),location.getY() + (size->getY()/200));
	//Turn direction into a positive/negative modifier
	int directionalModifierX = 1;
	int directionalModifierY = 1;
	if(direction->getX() < 0) {	directionalModifierX = -1; }
	if(direction->getY() < 0) {	directionalModifierY = -1; }

	
	point2d* probeOne = new point2d(midPoint->getX() + 0.25*directionalModifierX, midPoint->getY() + 0.25*(-directionalModifierY));
	point2d* probeTwo = new point2d(midPoint->getX() + 0.25*(-directionalModifierX), midPoint->getY() + 0.25*(directionalModifierY));
	point2d* probeOneEndPoint = new point2d(probeOne->getX() + direction->getX(),probeOne->getY() + direction->getY());
	point2d* probeTwoEndPoint = new point2d(probeTwo->getX() + direction->getX(),probeTwo->getY() + direction->getY());
	control* ctrl = control::getInstance();
	vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
	cout<<"LOCATION = "<<location.getX()<<" "<<location.getY()<<endl;
	cout<<"PROBE POINTS "<<probeOne->getX()<<" "<<probeOne->getY()<<endl;
	cout<<"PROBEEnd POINTS "<<probeOneEndPoint->getX()<<" "<<probeOneEndPoint->getY()<<endl;
	cout<<"PROBE POINTS TWO "<<probeTwo->getX()<<" "<<probeTwo->getY()<<endl;
	cout<<"PROBEEnd POINTS TWO "<<probeTwoEndPoint->getX()<<" "<<probeTwoEndPoint->getY()<<endl;
	//for(int a=0;a<64;a++) {
	//	for(int b=0;b<64;b++) {
	//		cout<<grd->at(a).at(b)->getMovable();
	//	}
	//	cout<<endl;
	//}
	cout<<raytrace(probeOne->getX(),probeOne->getY(),probeOneEndPoint->getX(),probeOneEndPoint->getY())<<endl;
	cout<<raytrace(probeTwo->getX(),probeTwo->getY(),probeTwoEndPoint->getX(),probeTwoEndPoint->getY())<<endl;
	if(raytrace(probeOne->getX(),probeOne->getY(),probeOneEndPoint->getX(),probeOneEndPoint->getY())) 
	{
		getCollisionNormal(rayTraceXCollide,rayTraceYCollide,*probeOne,*probeOneEndPoint,1);
	}
	if(raytrace(probeTwo->getX(),probeTwo->getY(),probeTwoEndPoint->getX(),probeTwoEndPoint->getY())) 
	{
		getCollisionNormal(rayTraceXCollide,rayTraceYCollide,*probeTwo,*probeTwoEndPoint,1);
	}
	//if(grd->at((int)probeOneEndPoint->getY()).at((int)probeOneEndPoint->getX())->getMovable() == 0) 
	//{
	//	getCollisionNormal((int)probeOneEndPoint->getX(),(int)probeOneEndPoint->getY(),*probeOne,*probeOneEndPoint,1);
	//}
	//if(grd->at((int)probeTwoEndPoint->getY()).at((int)probeTwoEndPoint->getX())->getMovable() == 0) 
	//{
	//	getCollisionNormal((int)probeTwoEndPoint->getX(),(int)probeTwoEndPoint->getY(),*probeTwo,*probeTwoEndPoint,1);
	//}
}

// Get normal of the side the probe will collide with to determine steering force
void unit::getCollisionNormal(float x,float y,point2d probeStartPoint,point2d probeEndPoint,float size) {

	// Four sides in order Top,Right,Bottom,Left
	vector<point2d>* startPoints = new vector<point2d>();
	vector<point2d>* endPoints = new vector<point2d>();
	startPoints->push_back(point2d(x,y+size));
	endPoints->push_back(point2d(x+size,y+size));
	startPoints->push_back(point2d(x+size,y));
	endPoints->push_back(point2d(x+size,y+size));
	startPoints->push_back(point2d(x+size,y));
	endPoints->push_back(point2d(x,y));
	startPoints->push_back(point2d(x,y+size));
	endPoints->push_back(point2d(x,y));
		point2d normal;
	for(int a=0;a<4;a++) {
		cout<<"TESTING SIDE "<<a<<" "<<DoLineSegmentsIntersect(startPoints->at(a).getX(),startPoints->at(a).getY(),endPoints->at(a).getX(),endPoints->at(a).getY(),
			probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY())<<endl;
		if(isIntersecting(startPoints->at(a),endPoints->at(a),probeStartPoint,probeEndPoint)) {
			cout<<"SIDE = "<<a<<endl;
			normal = getNormal(startPoints->at(a),endPoints->at(a));
			if(normal.getX() != 0) {
				cout<<"GOT HERE X"<<endl;
				int directionalModifierY = 1;
				if(direction->getY() < 0) {	directionalModifierY = -1; }
				direction->setX(0);
				direction->setY(1*directionalModifierY);
			}
			else {
				int directionalModifierX = 1;
				if(direction->getX() < 0) {	directionalModifierX = -1; }
				direction->setY(0);
				direction->setX(1*directionalModifierX);
				//direction->setY(direction->getY()*0.5);
			}
		}
	}


	//else if(isIntersecting(rightSideP1,rightSideP2,probeStartPoint,probeEndPoint)) {
	//	normal = getNormal(rightSideP1,rightSideP2);
	//}
	//else if(isIntersecting(bottomSideP1,bottomSideP2,probeStartPoint,probeEndPoint)) {
	//	normal = getNormal(bottomSideP1,bottomSideP2);
	//}
	//else if(isIntersecting(leftSideP1,leftSideP2,probeStartPoint,probeEndPoint)) {
	//	normal = getNormal(leftSideP1,leftSideP2);
	//}

	//cout<<"LEFT SIDE POINT COMPARISON ("<<leftSideP1.getX()<<" "<<leftSideP1.getY()<<") ("<<leftSideP2.getX()<<" "<<leftSideP2.getY()<<")"<<endl;
	//cout<<"TOP SIDE POINT COMPARISON ("<<topSideP1.getX()<<" "<<topSideP1.getY()<<") ("<<topSideP2.getX()<<" "<<topSideP2.getY()<<")"<<endl;
	//cout<<"RIGHT SIDE POINT COMPARISON ("<<rightSideP1.getX()<<" "<<rightSideP1.getY()<<") ("<<rightSideP2.getX()<<" "<<rightSideP2.getY()<<")"<<endl;
	//cout<<"BOTTOM SIDE POINT COMPARISON ("<<bottomSideP1.getX()<<" "<<bottomSideP1.getY()<<") ("<<bottomSideP2.getX()<<" "<<bottomSideP2.getY()<<")"<<endl;
//	cout<<"TESTING LEFT SIDE "<<DoLineSegmentsIntersect(leftSideP1.getX(),leftSideP1.getY(),leftSideP2.getX(),leftSideP2.getY(),
//		probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY())<<endl;
//	cout<<"TESTING TOP SIDE "<<DoLineSegmentsIntersect(topSideP1.getX(),topSideP1.getY(),topSideP2.getX(),topSideP2.getY(),
//		probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY())<<endl;
//	cout<<"TESTING RIGHT SIDE "<<DoLineSegmentsIntersect(rightSideP1.getX(),rightSideP1.getY(),rightSideP2.getX(),rightSideP2.getY(),
//		probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY())<<endl;
//	cout<<"TESTING BOTTOM SIDE "<<DoLineSegmentsIntersect(bottomSideP1.getX(),bottomSideP1.getY(),bottomSideP2.getX(),bottomSideP2.getY(),
//		probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY())<<endl;
}

bool unit::isIntersecting(point2d sideStartPoint, point2d sideEndPoint, point2d probeStartPoint, point2d probeEndPoint) {
	return DoLineSegmentsIntersect(sideStartPoint.getX(),sideStartPoint.getY(),sideEndPoint.getX(),sideEndPoint.getY(),
		probeStartPoint.getX(),probeStartPoint.getY(),probeEndPoint.getX(),probeEndPoint.getY());
}

point2d unit::getNormal(point2d startPoint, point2d endPoint) {
	return point2d(-(endPoint.getY()-startPoint.getY()),(endPoint.getX()-startPoint.getX()));
}
