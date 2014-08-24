#include "group.h"
#include "rectangle.h"
#include "control.h"
#include "collision.h"

group::group() {
	units = new vector<sprite*>();
}

bool group::contains(vector<sprite*> sprs) {
	vector<sprite*>::iterator it;
	vector<sprite*>* newVec = new vector<sprite*>();
	for(it = units->begin(); it != units->end();)
	{
		bool remove = false;
		for(int b=0;b<sprs.size();b++) {
			if((*it)->getUnitId() == sprs.at(b)->getUnitId()) {
				remove = true;
				break;
			}
		}
		if(remove == false) {
			newVec->push_back((*it));
		}
		it++;

	}
	units = newVec;
	return true;
}

void group::steer() {
	float xVel = 0;
	float yVel = 0;
	for(int a=0;a<units->size();a++) {
		xVel += units->at(a)->getVelocity()->getX();
		yVel += units->at(a)->getVelocity()->getY();
	}
	xVel = xVel/units->size();
	yVel = yVel/units->size();
	//for(int a=0;a<units->size();a++) {
	//	if(!(units->at(a)->getVelocity()->getX() == 0 && units->at(a)->getVelocity()->getY() == 0) && !(units->at(a)->getEndPath())) {
	//		//units->at(a)->setVelocity(xVel,yVel);
	//		point2d* normal = collisionAvoidance(units->at(a));
	//		if(normal != NULL) {
	//			if(normal->getX() != 0 ) {
	//				xVel = -1;
	//			}
	//			if(normal->getY() != 0) {
	//				yVel  = -1;
	//			}
	//			cout<<"COLLIDED"<<endl;
	//			units->at(a)->setVelocity(xVel,yVel);
	//		}
	//		
	//	}
	//	
	//}
}

point2d* group::collisionAvoidance(sprite* unit) {
	point2d move(unit->getPosition().getX() + unit->getVelocity()->getX(),unit->getPosition().getY() + unit->getVelocity()->getY());
	point2d* collided = avoidance(
		unit->getPosition().getX()  + unit->getSize()->getX()/100, 
		unit->getPosition().getY() + unit->getSize()->getY()/100,
		unit->getPosition().getX() + unit->getSize()->getX()/100 + unit->getVelocity()->getX(),
		unit->getPosition().getY() + unit->getSize()->getY()/100 + unit->getVelocity()->getY(),
		move,unit->getSize(),unit->getUnitId(),unit);
	if(collided == NULL) {
		collided = avoidance(
		unit->getPosition().getX(), 
		unit->getPosition().getY(),
		unit->getPosition().getX() + unit->getVelocity()->getX(),
		unit->getPosition().getY() + unit->getVelocity()->getY(),
		move,unit->getSize(),unit->getUnitId(),unit);
	}
	return collided;
}

void group::setUnits(vector<sprite*> selected) {
	for(int a=0;a<selected.size();a++) {
		selected.at(a)->setLeader(leader);
		units->push_back(selected.at(a));
	}
}

// Functions to determine at what point the unit will collided with the other sprite and at what directions it should turn to avoid
point2d* group::calculateNormal(sprite* collided, point2d* sp, point2d* ep) {
	point2d* normal = NULL;
	vector<point2d*> linePoints;
	// bottom left
	linePoints.push_back(&collided->getPosition());
	// bottom right
	linePoints.push_back(new point2d(collided->getPosition().getX() + collided->getSize()->getX(),collided->getPosition().getY()));
	// top right
	linePoints.push_back(new point2d(collided->getPosition().getX() + collided->getSize()->getX(),collided->getPosition().getY()  + collided->getSize()->getY()));
	// top left
	linePoints.push_back(new point2d(collided->getPosition().getX(),collided->getPosition().getY()  + collided->getSize()->getY()));

	for( int a=0;a<4;a++) {
		point2d* endPoint;
		if(a == 3) {
			endPoint = linePoints.at(0);
		}
		else {
			endPoint = linePoints.at(a + 1);
		}

		point2d* intersec = intersection(linePoints.at(a),
			endPoint,
			sp,
			ep);
		if(intersec != NULL) {
			// Holds distance from intersection point to start point of unit for future direction calculates in other functions
			currentDistanceHolder = 0;
			currentDistanceHolder += abs(intersec->getX() - sp->getX());
			currentDistanceHolder += abs(intersec->getY() - sp->getY());
			normal = new point2d(-(endPoint->getY() - linePoints.at(a)->getY()),-(endPoint->getX() - linePoints.at(a)->getX()));
		}
	}
	return normal;
}


point2d* group::avoidance(int x0, int y0, int x1, int y1, point2d move, point2d* size, int unitId, sprite* unit) {
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
		if(grd->at(y).at(x)->getMovable() == 0) {
			point2d* tmpNormal = calculateNormal(grd->at(y).at(x),new point2d(x0,y0),new point2d(x1,y1));
			if(tmpNormal != NULL) {

				return tmpNormal;
			}
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(x,y);
		if(sprsInTile.size() != 0) {
			for(int a=0;a<sprsInTile.size();a++){
				if(sprsInTile.at(a)->getUnitId() == unitId) {
					continue;
				}
				
				point2d* tmpNormal = calculateNormal(sprsInTile.at(a),new point2d(x0,y0),new point2d(x1,y1));
				if(tmpNormal != NULL) {
					if(checkCollisionDirection(sprsInTile.at(a),unit)) {
						return NULL;
					}
					return tmpNormal;
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
	return NULL;
}

point2d* group::intersection(point2d* p1, point2d* p2, point2d* p3, point2d* p4) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1->getX(), x2 = p2->getX(), x3 = p3->getX(), x4 = p4->getX();
	float y1 = p1->getY(), y2 = p2->getY(), y3 = p3->getY(), y4 = p4->getY();

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

	// Check if the x and y coordinates are within both lines
	if ( x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4) ) return NULL;
	if ( y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4) ) return NULL;

	// Return the point of intersection
	return new point2d(x,y);
}

bool group::checkCollisionDirection(sprite* colSpr,sprite* unit) {
	if((colSpr->getVelocity()->getX()*unit->getVelocity()->getX() > 0.0 && colSpr->getVelocity()->getX() != 0) && 
		(colSpr->getVelocity()->getY()*unit->getVelocity()->getY() > 0.0 && colSpr->getVelocity()->getY() != 0)) {
			return true;
	}
	return false;
}