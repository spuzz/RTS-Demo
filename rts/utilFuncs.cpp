#include "utilFuncs.h"

std::vector<sprite*>* utilFuncs::erase(std::vector<sprite*>* myNumbers_in, sprite* number_in)
{
	std::vector<sprite*>::iterator iter = myNumbers_in->begin();
	std::vector<sprite*>::iterator endIter = myNumbers_in->end();
	for(; iter != endIter; ++iter)
	{
		if((*iter)->getUnitId() == number_in->getUnitId())
		{
			myNumbers_in->erase(iter);
			break;
		}
	}
	return myNumbers_in;
}

std::vector<aStarNode*>* utilFuncs::erase(std::vector<aStarNode*>* myNumbers_in, aStarNode* number_in)
{
	std::vector<aStarNode*>::iterator iter = myNumbers_in->begin();
	std::vector<aStarNode*>::iterator endIter = myNumbers_in->end();
	for(; iter != endIter; ++iter)
	{
		if(*iter == number_in)
		{
			myNumbers_in->erase(iter);
			break;
		}
	}
	return myNumbers_in;

}

float utilFuncs::manhattenDistance(float p1x, float p1y, float p2x, float p2y) {
	float distance = 0;
	distance += abs(p1x - p2x);
	distance += abs(p1y - p2y);
	return distance;
}

float utilFuncs::manhattenDistance(point2d p1, point2d p2) {
	float distance = 0;
	distance += abs(p1.getX() - p2.getX());
	distance += abs(p1.getY() - p2.getY());
	return distance;
}