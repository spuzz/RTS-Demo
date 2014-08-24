#include "collision.h"
#include "collisionGrid.h"

#define EPSILON 0.0001   // Define your own tolerance.
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

collision::collision() {

}
bool collision::pathFindingTargetCollision(point2d* point, rectangle rect,float speed) {
	if((point->getX() >= rect.getStartPoint()->getX() - speed || FLOAT_EQ(point->getX(),rect.getStartPoint()->getX() - speed)) && 
		(point->getX() <= rect.getEndPoint()->getX() + speed|| FLOAT_EQ(point->getX(),rect.getEndPoint()->getX() + speed)) && 
		(point->getY() <= rect.getStartPoint()->getY() + speed || FLOAT_EQ(point->getY(),rect.getStartPoint()->getY() + speed)) && 
		(point->getY() >= rect.getEndPoint()->getY() - speed || FLOAT_EQ(point->getY(),rect.getEndPoint()->getY() - speed)))
	{
		return true;
	}
	return false;
}

bool collision::pointToRectCollision(point2d* point, rectangle rect) {
	//logging::log(logging::BASIC,point->getX());
	//logging::log(logging::BASIC,point->getY());
	//logging::log(logging::BASIC,rect.getStartPoint()->getX());
	//logging::log(logging::BASIC,rect.getStartPoint()->getY());
	//logging::log(logging::BASIC,rect.getEndPoint()->getX());
	//logging::log(logging::BASIC,rect.getEndPoint()->getY());
	if((point->getX() >= rect.getStartPoint()->getX() || FLOAT_EQ(point->getX(),rect.getStartPoint()->getX())) && 
		(point->getX() <= rect.getEndPoint()->getX()|| FLOAT_EQ(point->getX(),rect.getEndPoint()->getX())) && 
		(point->getY() >= rect.getStartPoint()->getY() || FLOAT_EQ(point->getY(),rect.getStartPoint()->getY())) && 
		(point->getY() <= rect.getEndPoint()->getY() || FLOAT_EQ(point->getY(),rect.getEndPoint()->getY())))
	{
		return true;
	}
	return false;
}

bool collision::pathCollision(point2d* pos,point2d* size, int unitId) {
	control* ctrl = control::getInstance();
	rectangle compareRect(new point2d(pos->getX()*100,pos->getY()*100),new point2d(pos->getX()*100+size->getX(),pos->getY()*100+size->getY()));
	rectangle tileRect(new point2d((int)pos->getX(),(int)pos->getY()),new point2d((int)(pos->getX()+(size->getX()/100)),(int)(pos->getY()+(size->getY()/100))));
	vector<point2d*> tmpTiles = collision::checkTiles(tileRect);
	vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
	collisionGrid* qdTree = ctrl->getColTree();
	// after calculating tiles, determine if each of these tiles is traversable
	for(int a=0;a<tmpTiles.size();a++) {
		if((tmpTiles[a]->getY() > (grd->size() - 1)) || (tmpTiles[a]->getY() < 0) || (tmpTiles[a]->getX() > (grd->at(tmpTiles[a]->getY()).size() - 1)) ||
			 (tmpTiles[a]->getX() < 0)) { 
				cout<<"COLLISION"<<endl;
				return true;
		}
		if(grd->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
			cout<<"COLLISION"<<endl;
			return true;
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(tmpTiles[a]->getX(),tmpTiles[a]->getY());
		rectangle* rect;
		for(int b=0;b<sprsInTile.size();b++) {
			sprite* spr = sprsInTile[b];
			if(spr->getUnitId() == unitId) { continue; }
			rect = new rectangle(new point2d(spr->getPosition().getX()*100,spr->getPosition().getY()*100),
				new point2d(spr->getPosition().getX()*100+spr->getSize()->getX(),
				spr->getPosition().getY()*100+spr->getSize()->getY()));
			if(rect->isOverLap(compareRect)) {
				cout<<"COLLISION"<<endl;
				return true;
			}
		}
	}
	return false;
}

vector<point2d*> collision::testCollision(point2d pos,point2d* size,int damage,int unitId, string colour) {
	control* ctrl = control::getInstance();
	rectangle compareRect(new point2d(pos.getX()*100,pos.getY()*100),new point2d(pos.getX()*100+size->getX(),pos.getY()*100+size->getY()));
	rectangle tileRect(new point2d((int)pos.getX(),(int)pos.getY()),new point2d((int)(pos.getX()+(size->getX()/100)),(int)(pos.getY()+(size->getY()/100))));
	QTime timer;
	timer.start();
	vector<point2d*> tmpTiles = collision::checkTiles(tileRect);
	vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
	collisionGrid* qdTree = ctrl->getColTree();
	// after calculating tiles, determine if each of these tiles is traversable
	for(int a=0;a<tmpTiles.size();a++) {
		// main control singleton access to tile grid
		if(grd->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
			return vector<point2d*>();
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(tmpTiles[a]->getX(),tmpTiles[a]->getY());
		rectangle* rect;
		for(int b=0;b<sprsInTile.size();b++) {
			sprite* spr = sprsInTile[b];
			if(spr->getUnitId() == unitId) { continue; }
			rect = new rectangle(new point2d(spr->getPosition().getX()*100,spr->getPosition().getY()*100),
				new point2d(spr->getPosition().getX()*100+spr->getSize()->getX(),
				spr->getPosition().getY()*100+spr->getSize()->getY()));
			if(rect->isOverLap(compareRect)) {
				if(spr->getColour() != colour) {
					cout<<"HIT THEM DAM IT "<<spr->getHealth()<<endl;
					spr->hit(damage);
				}
				return vector<point2d*>();
			}
		}

	}
	return tmpTiles;
}


sprite* collision::spriteCollision(point2d pos,point2d* size,int damage,int unitId, string colour) {
	control* ctrl = control::getInstance();
	rectangle compareRect(new point2d(pos.getX()*100,pos.getY()*100),new point2d(pos.getX()*100+size->getX(),pos.getY()*100+size->getY()));
	rectangle tileRect(new point2d((int)pos.getX(),(int)pos.getY()),new point2d((int)(pos.getX()+(size->getX()/100)),(int)(pos.getY()+(size->getY()/100))));
	QTime timer;
	timer.start();
	vector<point2d*> tmpTiles = collision::checkTiles(tileRect);
	vector<vector<tile*>>* grd = ctrl->getMainGrid()->getGrid();
	collisionGrid* qdTree = ctrl->getColTree();
	// after calculating tiles, determine if each of these tiles is traversable
	for(int a=0;a<tmpTiles.size();a++) {
		// main control singleton access to tile grid
		if(grd->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX())->getMovable() == 0) {
			return grd->at(tmpTiles[a]->getY()).at(tmpTiles[a]->getX());
		}
		vector<sprite*> sprsInTile = ctrl->getColTree()->getSpritesInTile(tmpTiles[a]->getX(),tmpTiles[a]->getY());
		rectangle* rect;
		for(int b=0;b<sprsInTile.size();b++) {
			sprite* spr = sprsInTile[b];
			if(spr->getUnitId() == unitId) { continue; }
			rect = new rectangle(new point2d(spr->getPosition().getX()*100,spr->getPosition().getY()*100),
				new point2d(spr->getPosition().getX()*100+spr->getSize()->getX(),
				spr->getPosition().getY()*100+spr->getSize()->getY()));
			if(rect->isOverLap(compareRect)) {
				if(spr->getColour() != colour) {
					spr->hit(damage);
				}
				return spr;
			}
		}

	}
	return NULL;
}

/* Determine which tiles the new sprite position overlaps. Used to determine if the pos the sprite
   is attempting to move to is passable */

vector<point2d*> collision::checkTiles(rectangle spr) {
	vector<point2d*> tiles;
	bool result = false;
	point2d* tmp;
	for(int a=spr.getStartPoint()->getX();a<=spr.getEndPoint()->getX();a++) {
		for(int b=spr.getStartPoint()->getY();b<=spr.getEndPoint()->getY();b++) {
			tiles.push_back(new point2d(a,b));
		}
	}
	return tiles;
}

bool collision::checkCurrentTiles(vector<point2d*> tiles,point2d* p1) {
	for(int a=0;a<tiles.size();a++) {
		if(tiles[a]->compare(p1)) {
			return true;
		}
	}
	return false;
}