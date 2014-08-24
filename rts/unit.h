#pragma once

#include "sprite.h"
#include <map>
#include "aStar.h"
#include "aStarNode.h"


class unit : public sprite {

public:
	//constructors
	unit();

	//main methods
	string update();
	bool checkReachedPathPoint(int pathLocation,vector<aStarNode*> tmpPathVector);
	bool isIntersecting(point2d sideStartPoint, point2d sideEndPoint, point2d probeStartPoint, point2d probeEndPoint);
	void calculateDirection();
	bool collision(float x,float y);
	void createAbilities(map<string,map<string,string>> xmlValues);
	void setup(map<string,string> xmlValues);
	void examinePathDirection(int pathLocation,vector<aStarNode*> tmpPathVector);
	void moveUnit(vector<point2d*> tiles, point2d move);
	void move();
	void updateGoal(point2d* tar, bool att);
	void updatePath(aStar* p);
	void getCollisionNormal(float x,float y,point2d probeStartPoint,point2d probeEndPoint,float size);

	bool LineSegmentLineSegmentIntersection( point2d l1p1, point2d l1p2, point2d l2p1, point2d l2p2);
	int pathSmooth(vector<aStarNode*> path, int current);
	aStar* getPath() { return path; }
	point2d* checkVision();
	point2d getNormal(point2d startPoint, point2d endPoint);
	// update the adjustment to control group movement
	void updatePathAdjustment(float x, float y) { xPathAdj = x; yPathAdj = y;};
	void probeDirection();
	//setters and getters
	void hit(int ouch) { health -= ouch; }
	void setMovementSpeed(float m) { movementSpeed = m; }
	void increaseMovementSpeed(float m) { movementSpeed += m; }
	void decreaseMovementSpeed(float m) { movementSpeed -= m; }

	float getMovementSpeed() { return movementSpeed; }
	bool getEndPath() { return (currentPath == pathVector.size()); }
	string getColour() { return colour; }

protected:

	bool raytrace(int x0, int y0, int x1, int y1);
	bool avoidance(float moveX, float moveY);

	//Variables holding where the raytrace found a collision to use in other methods
	int rayTraceXCollide;
	int rayTraceYCollide;

	aStar* path;
	aStar* localPath;
	bool usingLocal;
	bool smooth;
	int yNegative;
	int xNegative;

	int currentPath, localCurrentPath;
	float movementSpeed;
	vector<ability*> tierBuildings;
	vector<aStarNode*> pathVector, localPathVector;
	
	void determineTarget();

	// Flocking Behaviour
	unit* groupLeader;
	bool isGroupLeader;

private:

};