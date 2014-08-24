#include "building.h"
#include "qobject.h"
#include "control.h"
#include "collision.h"

building::building()  : sprite() {
	health = 100;
	maxHealth = 100;
	damage = 5;
	armor = 1;
	range = 0;
	working = false;
	//movable = false;
}
void building::setup(map<string,string> xmlValues) {
	health = atoi(xmlValues["health"].c_str());
	maxHealth = atoi(xmlValues["health"].c_str());
	damage = atoi(xmlValues["damage"].c_str());
	armor = atoi(xmlValues["armor"].c_str());
	range = atoi(xmlValues["health"].c_str());
	setSize(atof(xmlValues["sizeX"].c_str()),atof(xmlValues["sizeY"].c_str()));
	updateTiles();
}

void building::updateTiles() {
	control* ctrl = control::getInstance();
	rectangle tileRect(new point2d((int)location.getX(),(int)location.getY()),new point2d((int)(location.getX()+(size->getX()/100)),(int)(location.getY()+(size->getY()/100))));
	vector<point2d*> tmpTiles = collision::checkTiles(tileRect);
	for(int a=0;a<tiles.size();a++) {
		ctrl->getColTree()->removeSpriteInTile(this);
	}
	tiles = tmpTiles;
	ctrl->getColTree()->addSpriteToTile(this);
}

void building::useBuild(string name) {
	logging::log(logging::FINEST,"Building ability used");
	QObject* test = new QObject();
	working = true;
	timer.restart();
	buildObject = name;

}

string building::update() {
	if(health <= 0) {
		return "dead";
	}
	if(timer.elapsed() > 1000 && working == true) {
		control* ctrl = control::getInstance();
		ctrl->addPlayerUnit(buildObject,getPosition().getX()*100,(getPosition().getY()-1)*100);
		working = false;
	}
	return "alive";
}

void building::createAbilities(map<string,map<string,string>> xmlValues) {
	for ( map<string,map<string,string>>::const_iterator iter = xmlValues.begin();
		iter != xmlValues.end(); ++iter ) {
			string name = iter->first;
			map<string,string> tmp = iter->second;
			ability* ab = ability::create(iter->first,tmp["image"] + ".png",tmp);
			addAbility(ab);
	}

}