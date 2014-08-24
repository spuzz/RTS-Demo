#include "point2d.h"


using namespace std;
point2d::point2d() {
	x = 0;
	y = 0;
}


point2d::point2d(float xIn, float yIn) {
	x = xIn;
	y = yIn;
}


// public methods
point2d point2d::multiply(float m) {
	float xTmp = x * m;
	float yTmp = y * m;
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::multiply(point2d p) {
	float xTmp = x * p.getX();
	float yTmp = y * p.getY();
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::divide(float m){
	float xTmp = x/m;
	float yTmp = y/m;
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::divide(point2d p){
	float xTmp = x/p.getX();
	float yTmp = y/p.getY();
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::add(float m){
	float xTmp = x+m;
	float yTmp = y+m;
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::add(point2d p){
	float xTmp = x+p.getX();
	float yTmp = y+p.getY();
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::subtract(float m){
	float xTmp = x-m;
	float yTmp = y-m;
	point2d point(xTmp,yTmp);
	return point;
}

point2d point2d::subtract(point2d p){
	float xTmp = x-p.getX();
	float yTmp = y-p.getY();
	point2d point(xTmp,yTmp);
	return point;
}

// getters and setters
void point2d::setPoint(float xIn, float yIn) {
	x = xIn;
	y = yIn;
}

bool point2d::compare(point2d* p1) {
	if(p1->getX() == getX() && p1->getY() == getY()) {
		return true;
	}
	return false;
}

float rounding( float no )
{
     int x, temp;
     float y;
     temp = x = no;   //only the integer part is taken 
     y = no -  x; // u get the decimal number here 
     y*=100; //decimal gets converted to 2 digit no n 1 decimal
     x = y;
     y-= x;  //the last decimal is stored in y 
     if( y >= 0.5 )
             x++ ;
    return (float(temp) + float(x)/100) ;
}

void point2d::setX(float xIn) {
	x = rounding(xIn);
}
void point2d::setY(float yIn) {
	y = rounding(yIn);
}


