#pragma once

#include <string>
#include <iostream>

using namespace std;

class point2d {

public:
	// constructors
	point2d();
	point2d(float x, float y);

	// public methods
	point2d multiply(float m);
	point2d multiply(point2d p);

	point2d divide(float m);
	point2d divide(point2d p);

	point2d add(float m);
	point2d add(point2d p);

	point2d subtract(float m);
	point2d subtract(point2d p);

	bool compare(point2d* p1);
	friend bool operator== (point2d &cP1, point2d &cP2)
	{
		if(cP1.getX() == cP2.getX() &&
			cP1.getY() == cP2.getY()) {
				return true;
		} else {
			return false;
		}
	}

	// getters and setters
	float getX() {return x;}
	float getY() {return y;}
	void setPoint(float x, float y);
	void setX(float xIn);
	void setY(float yIn);
	
private:
	// private variables
	float x,y;
	// private methods
	
};