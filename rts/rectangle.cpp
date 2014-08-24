#include "rectangle.h"

rectangle::rectangle() {

}

rectangle::rectangle(point2d* s,point2d* e) {
	setPoints(s,e);
}

bool rectangle::isOverLap(rectangle rect)
{
	if(start->getX() < rect.getEndPoint()->getX() && end->getX() > rect.getStartPoint()->getX() &&
		start->getY() < rect.getEndPoint()->getY() && end->getY() > rect.getStartPoint()->getY()) {
		return true;
	}
	return false;
	//if ((start->getX() <= rect.getStartPoint()->getX() && rect.getEndPoint()->getX() >= end->getX()) 
	//	&&(start->getY() >= rect.getStartPoint()->getY() && rect.getEndPoint()->getY() >= end->getY()))
	//{
	//	return true;
	//} else
	//if (( rect.getStartPoint()->getX()<= start->getX() && end->getX() <= rect.getEndPoint()->getX()) 
	//	&&( rect.getStartPoint()->getY() >= start->getY() && rect.getEndPoint()->getY() >=  rect.getEndPoint()->getY()))
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

bool rectangle::isUnder(rectangle rect)
{
	if(start->getX() <= rect.getStartPoint()->getX() && end->getX() >= rect.getEndPoint()->getX() &&
		start->getY() >= rect.getStartPoint()->getY() && end->getY() <= rect.getEndPoint()->getY()) {
		return true;
	}
	return false;
	//if ((start->getX() <= rect.getStartPoint()->getX() && rect.getEndPoint()->getX() >= end->getX()) 
	//	&&(start->getY() >= rect.getStartPoint()->getY() && rect.getEndPoint()->getY() >= end->getY()))
	//{
	//	return true;
	//} else
	//if (( rect.getStartPoint()->getX()<= start->getX() && end->getX() <= rect.getEndPoint()->getX()) 
	//	&&( rect.getStartPoint()->getY() >= start->getY() && rect.getEndPoint()->getY() >=  rect.getEndPoint()->getY()))
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}