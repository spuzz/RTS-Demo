#include "playerControl.h"
#include "rectangle.h"
#include "control.h"
#include "xmlparser.h"
#include "utilFuncs.h"
#include <algorithm>

int playerControl::unitId = 0;

playerControl::playerControl() {
	totalTime = 0;
	textureMap();
	setupFow(64,64);
}

playerControl::playerControl(string col,map<string,map<string,string>> sMap,map<string,map<string,map<string,string>>> aMap,int width, int height) {
	colour = col;
	
	spriteMap = sMap;
	abilityMap = aMap;
	totalTime = 0;
	textureMap();
	setupFow(width,height);
}

void playerControl::setupFow(int width, int height) {
	fowControl = new fogofwar(width,height);
}

void playerControl::update(bool neutral) {
	vector<unit*> removeUnit;
	

	for(int a=0;a<playerUnits.size();a++) {
		string results = playerUnits[a]->update();

		if(results != "dead") {
			removeUnit.push_back(playerUnits[a]);

		}
		else {
			control* ctrl = control::getInstance();
			ctrl->getColTree()->removeSpriteInTile(playerUnits[a]);
		}
	}
	playerUnits = removeUnit;
	removeUnit.clear();
	vector<building*> removeBuilding;
	for(int a=0;a<playerBuildings.size();a++) {
		string results = playerBuildings[a]->update();
		if(results != "dead") {
			removeBuilding.push_back(playerBuildings[a]);
			
		}
		else {
			control* ctrl = control::getInstance();
			ctrl->getColTree()->removeSpriteInTile(playerBuildings[a]);
		}
	}
	playerBuildings = removeBuilding;
	for(int g=0;g<groupMoveSelections.size();g++) {
		groupMoveSelections.at(g).steer();
	}
	for(int a=0;a<playerUnits.size();a++) {
		playerUnits.at(a)->move();
	}
	if(neutral == false) {
		updateFow();
	}
	
}

void playerControl::updateFow() {
	fowControl->clear();
	for(int a=0;a<playerUnits.size();a++) {
		fowControl->addVision(playerUnits.at(a)->getPosition().getX(),playerUnits.at(a)->getPosition().getY(),9);
	}
	for(int a=0;a<playerBuildings.size();a++) {
		fowControl->addVision(playerBuildings.at(a)->getPosition().getX(),playerBuildings.at(a)->getPosition().getY(),9);
	}
}

void playerControl::selectFeature() {

}

void playerControl::selectGroup() {

}

void playerControl::switchSelectToGroup() {

}

void playerControl::createGroup() {

}

void playerControl::updateGroupPath(unit* lead, aStar* completedPath) {
	lead->updatePath(completedPath);
	for(int a=0;a<groupMoveSelections.size();a++) {
		if(groupMoveSelections.at(a).getLeader()->getUnitId() == lead->getUnitId()) {
			for(int b=0;b<groupMoveSelections.at(a).getUnits()->size();b++) {
				sprite* tmp = groupMoveSelections.at(a).getUnits()->at(b);
				float xTar = tmp->getPosition().getX() - lead->getPosition().getX();
				float yTar = tmp->getPosition().getY() - lead->getPosition().getY();
				xTar = 0;
				yTar = 0;
				point2d* finalTarget = new point2d(groupMoveSelections.at(a).getTarget()->getX() + xTar
					,groupMoveSelections.at(a).getTarget()->getY() + yTar);
				
				//tmp->updatePathAdjustment(xTar, yTar);
				tmp->updateGoal(finalTarget,true);
				// BAD HACK DUE TO WIERD CIRCULAR INCLUDE IN SPRITE/ASTAR
				for(int a=0;a<playerUnits.size();a++) {
					if(playerUnits.at(a)->getUnitId() == tmp->getUnitId()) {
						playerUnits.at(a)->updatePath(completedPath);
					}
				}
			}
			
		}
	}
}
// Move currently selected units based on current formation and enemy unit proximity
void playerControl::moveSelected(point2d target, bool attackMove) {
	control* ctrl = control::getInstance();
	//for(int a=0;a<groupMoveSelections.size();a++) {
	//	groupMoveSelections.at(a).contains(selected);
	//}
	sprite* leader = determineClosest(target);
	group newGroup;
	newGroup.setLeader(leader);
	newGroup.setUnits(selected);
	newGroup.setTarget(new point2d(target.getX(),target.getY()));
	groupMoveSelections.push_back(newGroup);
	leader->updateGoal(new point2d(target.getX(),target.getY()),attackMove);
	ctrl->getPathingQueue()->addPath((unit*)leader,this);
	groupMoveSelections.erase( remove_if( groupMoveSelections.begin(),groupMoveSelections.end(), &NeedsRemoval), groupMoveSelections.end() );
}

// Calculates from current selection, which unit is closest to the target point (making this unit the leader)
sprite* playerControl::determineClosest(point2d target) {
	sprite* leader = selected.at(0);
	float targetDistance = utilFuncs::manhattenDistance(leader->getPosition(),target);
	for(int a=1;a<selected.size();a++) {
		float tmpDistance = utilFuncs::manhattenDistance(selected.at(a)->getPosition(),target);
		if(tmpDistance < targetDistance) {
			leader = selected.at(a);
			targetDistance = tmpDistance;
		}
	}
	return leader;
}

void playerControl::addBuilding(string name,float x, float y) {
	logging::log(logging::FINEST,"Creating building");
	QTime timerTest;
	timerTest.start();
	newBuilding = new building();
	newBuilding->setColour(colour);
	newBuilding->setPosition(x,y);
	newBuilding->setUnitId(unitId);
	newBuilding->createTexture(getTerrainTexture(name),name + colour + ".png");
	//string configFile="Data/units.xml"; // stat file. Get ambigious segfault otherwise.
	//

	//GetConfig appConfig;
	//
	//map<string,map<string,string>*> result = appConfig.readConfigFile(configFile,name,"building");
	//map<string,map<string,map<string,string>>*> abilities = appConfig.getAbilityMap();

	
	newBuilding->setup(spriteMap[name]);
	newBuilding->createAbilities(abilityMap[name]);
	newBuilding->createDisplayList();
	playerBuildings.push_back(newBuilding);
	unitId++;
	totalTime += timerTest.elapsed();
}

void playerControl::addUnit(string name, float x, float y) {
	logging::log(logging::FINEST,"Creating unit");
	unit* newUnit;
	newUnit = new unit();
	newUnit->setColour(colour);
	newUnit->setPosition(x,y);
	newUnit->setUnitId(unitId);
	newUnit->createTexture(getTerrainTexture(name), name + colour + ".png");
	//string configFile="Data/units.xml";

	//GetConfig appConfig;

	//map<string,string> result = appConfig.readConfigFile(configFile,name,"unit");
	//map<string,map<string,string>> abilities = appConfig.getAbilityMap();
	newUnit->setup(spriteMap[name]);
	newUnit->createAbilities(abilityMap[name]);
	newUnit->createDisplayList();
	playerUnits.push_back(newUnit);
	unitId++;
}


GLuint playerControl::getTerrainTexture(string key) {
	// get texture for individual tile from map file value
	return terrainTexture[key];
}

void playerControl::trySelect(float x, float y) {
	selected.clear();
	for(int a=0;a<playerBuildings.size();a++) {
		if(x >= playerBuildings[a]->getPosition().getX()*100 && x <= playerBuildings[a]->getPosition().getX()*100+100 && 
		y >= playerBuildings[a]->getPosition().getY()*100 && y <= playerBuildings[a]->getPosition().getY()*100+100) 
		{
			selected.push_back(playerBuildings[a]);
		}
	}
	for(int a=0;a<playerUnits.size();a++) {
		if(x >= playerUnits[a]->getPosition().getX()*100 && x <= playerUnits[a]->getPosition().getX()*100+100 && 
		y >= playerUnits[a]->getPosition().getY()*100 && y <= playerUnits[a]->getPosition().getY()*100+100) 
		{
			selected.push_back(playerUnits[a]);
		}
	}
}

void playerControl::trySelect(point2d* start, point2d* end) {
	control* ctrl = control::getInstance();
	selected.clear();
	rectangle compareRect(start,end);
	rectangle* rect;
	for(int a=0;a<playerUnits.size();a++) {
		if(selected.size() > 11) {
			return;
		}
		rect = new rectangle(new point2d(playerUnits[a]->getPosition().getX()*100,playerUnits[a]->getPosition().getY()*100),
			new point2d(playerUnits[a]->getPosition().getX()*100+100,playerUnits[a]->getPosition().getY()*100+100));
		if(rect->isOverLap(compareRect)) {
			selected.push_back(playerUnits[a]);
		}
	}
	if(selected.size() > 0) {
		return;
	}
	for(int a=0;a<playerBuildings.size();a++) {
		rect = new rectangle(new point2d(playerBuildings[a]->getPosition().getX()*100,playerBuildings[a]->getPosition().getY()*100),
			new point2d(playerBuildings[a]->getPosition().getX()*100+100,playerBuildings[a]->getPosition().getY()*100+100));

		if(rect->isOverLap(compareRect)) {
			selected.push_back(playerBuildings[a]);
		}
	}
	
	if(selected.size() == 0) {
		vector<playerControl*> ai = ctrl->getAIControl();
		for(int n=0;n<ai.size();n++) {
			for(int a=0;a<ai[n]->playerUnits.size();a++) {
				rect = new rectangle(new point2d(ai[n]->playerUnits[a]->getPosition().getX()*100,ai[n]->playerUnits[a]->getPosition().getY()*100),
					new point2d(ai[n]->playerUnits[a]->getPosition().getX()*100+100,ai[n]->playerUnits[a]->getPosition().getY()*100+100));
				if(rect->isOverLap(compareRect)) {
					selected.push_back(ai[n]->playerUnits[a]);
					return;
				}
			}
			for(int a=0;a<ai[n]->playerBuildings.size();a++) {
				rect = new rectangle(new point2d(ai[n]->playerBuildings[a]->getPosition().getX()*100,ai[n]->playerBuildings[a]->getPosition().getY()*100),
					new point2d(ai[n]->playerBuildings[a]->getPosition().getX()*100+100,ai[n]->playerBuildings[a]->getPosition().getY()*100+100));

				if(rect->isOverLap(compareRect)) {
					selected.push_back(ai[n]->playerBuildings[a]);
					return;
				}
			}
		}
	}

}

void playerControl::textureMap() {
	// build map object of texture files for comparison with map text file
	string building = "Data/building" + colour + ".png";
	terrainTexture["building"] = SOIL_load_OGL_texture
		(
		building.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	string swordsman = "Data/swordsman" + colour + ".png";
	terrainTexture["swordsman"] = SOIL_load_OGL_texture
		(
		swordsman.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);

	string drone = "Data/drone" + colour + ".png";
	terrainTexture["drone"] = SOIL_load_OGL_texture
		(
		drone.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	string tree = "Data/tree.png";
	terrainTexture["tree"] = SOIL_load_OGL_texture
		(
		tree.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	string wall = "Data/wall.png";
	terrainTexture["wall"] = SOIL_load_OGL_texture
		(
		wall.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	string goldmine= "Data/goldmine.png";
	terrainTexture["goldmine"] = SOIL_load_OGL_texture
		(
		goldmine.c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
}

void playerControl::setResources(int w,int g,int i,int p) {
	setWood(w);
	setGold(g);
	setIron(i);
	setPop(p);
}

vector<int> playerControl::getResources() {
	vector<int> resource;
	resource.push_back(wood);
	resource.push_back(gold);
	resource.push_back(iron);
	resource.push_back(population);
	return resource;
}

bool playerControl::checkResources() {
	return false;
}