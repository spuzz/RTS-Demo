

#include "control.h"	
#include "unitMapParser.h"
#include "tileMapParser.h"
#include <iostream>

// Main singleton class instance
control* control::m_pInstance = NULL;

control::control() {
}

void control::setUpInitial() {
	/*	
		Adding initial player units and building to the map.
		THIS NEEDS TO BE UPDATED to use a function that reads the
		map files so that different maps can be used and saved
	*/
	QTime timer;
	timer.start();
	string configFile="Data/units.xml"; // stat file. Get ambigious segfault otherwise.
	unitMapParser appConfig;
	tileMapParser appTest;
	map<string,map<string,string>> spriteMap = appConfig.readConfigFile(configFile);
	map<string,map<string,map<string,string>>> abilities = appConfig.getAbilityMap();
	droneBuilding = false;

	player = new playerControl("red",spriteMap,abilities,maingrid->getWidth(),maingrid->getHeight());
	allPlayerControllers.push_back(player);
	for(int a=0;a<200;a++) {
	}
	player->addUnit("swordsman",12,12);
	player->addUnit("swordsman",13,12);
	player->addUnit("swordsman",10,12);
	player->addUnit("swordsman",11,12);
	player->addUnit("swordsman",12,13);
	player->addUnit("swordsman",13,13);
	player->addUnit("swordsman",11,13);
	player->addUnit("swordsman",10,13);
	player->addUnit("swordsman",12,14);
	player->addUnit("swordsman",13,14);
	player->addBuilding("building",10,10);
	//player->addUnit("swordsman",17,22);

	playerControl* newAI = new playerControl("blue",spriteMap,abilities,maingrid->getWidth(),maingrid->getHeight());
	newAI->addBuilding("building",52,52);
	newAI->addUnit("drone",50,50);
	newAI->addUnit("drone",50,49);
	ai.push_back(newAI);

	createDroneBuilding("building","red");
	resource = new playerControl("black",spriteMap,abilities,maingrid->getWidth(),maingrid->getHeight());
	neutral = new playerControl("grey",spriteMap,abilities,maingrid->getWidth(),maingrid->getHeight());
	neutral->addBuilding("goldmine",5.0f,5.0f);
	neutral->addBuilding("goldmine",55,55);
	for(int a=0;a<maingrid->getTerrainGrid()->size();a++) {
		for(int b=0;b<maingrid->getTerrainGrid()->at(0).size();b++) {
			if(maingrid->getTerrainGrid()->at(a).at(b) != NULL) {
				//neutral->addBuilding("tree",b,a);
				//neutral->addBuilding("tree",float(b),float(a) + 0.5);
				//neutral->addBuilding("tree",float(b) + 0.5,float(a) + 0.5);
				//neutral->addBuilding("tree",float(b) + 0.25,float(a) + 0.25);
				//neutral->addBuilding("tree",float(b) + 0.5,float(a) + 0);
				//neutral->addBuilding("tree",float(b) + 0.75,float(a) + 0.25);
				//neutral->addBuilding("tree",float(b) + 0.25,float(a) - 0.25);
				//neutral->addBuilding("tree",float(b) + 0.75,float(a) - 0.25);
			}
		}
	}

	allPlayerControllers.push_back(player);
	allPlayerControllers.push_back(neutral);
	allPlayerControllers.push_back(resource);
	for(int a=0;a<ai.size();a++) {
		allPlayerControllers.push_back(ai[a]);
	}
	colTree->addPlayerSprites(player);
	for(int a=0;a<ai.size();a++) {
		colTree->addPlayerSprites(ai[a]);
	}
	colTree->addPlayerSprites(neutral);

	qdTree = new quadTree(getBuildingPositions(),getBuildingSizes(),getMainGrid()->getGrid(),64);


	

	stringstream ss;
	ss << "Total time take on initilisation = " << timer.elapsed();
	logging::log(logging::BASIC,"Initilisation has finished");
	logging::log(logging::INFO,ss.str());
	square = glGenLists(1);
	glNewList(square,GL_COMPILE);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0 );
			glVertex3f(0, 100, 0 );
			glVertex3f(100, 100, 0 );
			glVertex3f(100, 0, 0 );
		glEnd;
	glEndList();
	pathQueue = new pathingQueue();
	logicLock.start();
	logicLock.addMSecs(75);
	//cout<<"TIME TAKEN "<<timer.elapsed()<<endl;
}

void control::createDroneBuilding(string image, string colour) {
	droneBuild = new building();
	droneBuild->setColour(colour);
	droneBuild->setPosition(10,10);
	droneBuild->setUnitId(100000);
	string building = image + colour + ".png";
	droneBuild->createTexture(player->getTerrainTexture("building"),building);
	droneBuild->createDisplayList();
}
void control::setDroneBuildPos(float xpoint, float ypoint) {
	droneBuild->setPosition(xpoint,ypoint);
}

void control::addPlayerBuilding(float x, float y) {
	logging::log(logging::FINE,"Player building started");
	player->addBuilding("building",x/100,y/100);
	unitId++;
}

void control::addPlayerUnit(string name,float x, float y) {
	logging::log(logging::FINE,"Player unit started");
	player->addUnit(name,x/100,y/100);
	unitId++;
}


/* 
	Called when player selects something in main window, the coordinates of
	the mouse click are then compared to map info and the selection is
	added to the side bar
*/
void control::playerSelect(float x, float y) {
	logging::log(logging::FINEST,"single selection started");
	determineSelection(x,y);
	sdPanel->setNewSelection(player->getSelected());
}

void control::playerSelect(point2d* start, point2d* end) {
	logging::log(logging::FINEST,"Box selection used");
	determineSelection(start,end);
	sdPanel->setNewSelection(player->getSelected());
}

void control::determineSelection(float x, float y) {
	player->trySelect(x,y);
}

void control::determineSelection(point2d* start, point2d* end) {
	player->trySelect(start,end);
}

vector<sprite*> control::getPlayerSelect() {
	if(player->getSelected().size() > 0 && player->getSelected()[0]->getColour() == player->getColour()) {
		return player->getSelected();
	}
	return vector<sprite*>();
}

// This function gets building positions to avoid passing player control to multiple classes and avoiding some
// infinite reference issues
vector<point2d> control::getBuildingPositions() {
	vector<point2d> positions;
	for(int a=0;a<allPlayerControllers.size();a++) {
		for(int b=0;b<allPlayerControllers[a]->getBuildings()->size();b++) {
			positions.push_back(allPlayerControllers[a]->getBuildings()->at(b)->getPosition());
		}
	}
	return positions;
}

vector<point2d*> control::getBuildingSizes() {
	vector<point2d*> size;
	for(int a=0;a<allPlayerControllers.size();a++) {
		for(int b=0;b<allPlayerControllers[a]->getBuildings()->size();b++) {
			size.push_back(allPlayerControllers[a]->getBuildings()->at(b)->getSize());
		}
	}
	return size;
}
/* Function that is called on each frame from the opengl paintGL method */

void control::go() {

	
	//qdTree->reset();
	
	if(logicLock.elapsed() > 50) {
		QTime profile;
		profile.start();
		updateLogic();
		stringstream ss;
		ss << "Total time take on logic = " << profile.elapsed();
		//logging::log(logging::BASIC,ss.str());
		logicLock.restart();
	}
	QTime profile;
	profile.start();
	stringstream ss;
	render();
	ss << "Total time take on Rendering = " << profile.elapsed();
	//logging::log(logging::BASIC,ss.str());
	debug();

}

/* debug function */
void control::debug() {
	//colTree->PrintGrid();
	addQuadTreeLines();
}

void control::render() {
	maingrid->buildGrid(player->getFoW());

	sdPanel->updateInfo(player->getSelected());

	buildPlayer();

	buildAI();

	buildNeutral();

	attemptBuild();


}

void control::updateLogic() {
	player->update();
	for(int i=0;i<ai.size();i++) {
		ai[i]->update();
	}
	neutral->update(true);
	pathQueue->workPathing();
}

void control::addQuadTreeLines() {
	//float tmpWidth;
	//for(int a=0;a<qdTree->getMainQuadTreeNode()->getChildrenVector()->size();a++) {
	//	quadTreeNode* child = qdTree->getMainQuadTreeNode()->getChildrenVector()->at(a);
	//	glDisable(GL_BLEND);
	//	glPushMatrix(); 
	//	glLoadIdentity();
	//	tmpWidth =child->getWidth();
	//	point2d* tmpLoc = child->getLocation();
	//	glColor3f(0.0f,0.0,0.0);
	//	glBegin(GL_LINES);
	//		glVertex2f(tmpLoc->getX()*100, tmpLoc->getY()*100);
	//		glVertex2f(tmpLoc->getX()*100, (tmpLoc->getY() + tmpWidth)*100);
	//	glEnd();
	//	glBegin(GL_LINES);
	//		glVertex2f(tmpLoc->getX()*100, tmpLoc->getY()*100);
	//		glVertex2f((tmpLoc->getX() + tmpWidth)*100, tmpLoc->getY()*100);
	//	glEnd();
	//	glBegin(GL_LINES);
	//		glVertex2f(tmpLoc->getX()*100, (tmpLoc->getY() + tmpWidth)*100);
	//		glVertex2f((tmpLoc->getX() + tmpWidth)*100, (tmpLoc->getY() + tmpWidth)*100);
	//	glEnd();
	//	glBegin(GL_LINES);
	//		glVertex2f((tmpLoc->getX() + tmpWidth)*100, (tmpLoc->getY() + tmpWidth)*100);
	//		glVertex2f((tmpLoc->getX() + tmpWidth)*100, tmpLoc->getY()*100);
	//	glEnd();
	//	for(int b=0;b<child->getNeighbours()->size();b++) {
	//		quadTreeNode* parent = child->getNeighbours()->at(b);
	//		point2d* parentLoc = parent->getLocation();
	//		glBegin(GL_LINES);
	//			glVertex2f(tmpLoc->getX()*100 + child->getWidth()*50, tmpLoc->getY()*100 + child->getWidth()*50);
	//			glVertex2f(parentLoc->getX()*100 + parent->getWidth()*50, parentLoc->getY()*100 + parent->getWidth()*50);
	//		glEnd();
	//	}
	//	glColor3f(1.0f,1.0,1.0);

	//	glPopMatrix();
	//	glEnable(GL_BLEND);
	//}
}

void control::buildPlayer() {

	building* building;
	unit* unit;

	

	for(int a=0;a<player->getBuildings()->size();a++) {
		building = player->getBuildings()->at(a);
		glPushMatrix();
		float y = building->getPosition().getY();
		float x = building->getPosition().getX();
		
		glTranslatef(x*100,y*100,0);
		if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 511) {
			player->getBuildings()->at(a)->build();
		}
		glPopMatrix();
	}
	for(int a=0;a<player->getUnits()->size();a++) {
		unit = player->getUnits()->at(a);
		glPushMatrix();
		float y = unit->getPosition().getY();
		float x = unit->getPosition().getX();
		glTranslatef(x*100,y*100,0);
		if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 511) {
			player->getUnits()->at(a)->build();
		}
		glPopMatrix();
	}

}

void control::buildAI() {
	building* building;
	unit* unit;
	

	for(int i=0;i<ai.size();i++) {


		for(int a=0;a<ai[i]->getBuildings()->size();a++) {

			building = ai[i]->getBuildings()->at(a);
			glPushMatrix();
			float y = building->getPosition().getY();
			float x = building->getPosition().getX();
			glTranslatef(x*100,y*100,0);
			if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 511) {
				if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 0) {
					glColor3f(0.8f,0.8f,0.8f);
				}
				ai[i]->getBuildings()->at(a)->build();
			}

			glPopMatrix();

		}
		for(int a=0;a<ai[i]->getUnits()->size();a++) {

			unit = ai[i]->getUnits()->at(a);
			glPushMatrix();
			float y = unit->getPosition().getY();
			float x = unit->getPosition().getX();
			glTranslatef(x*100,y*100,0);
			if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 511) {
				if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 0) {
					glColor3f(0.8f,0.8f,0.8f);
				}
				ai[i]->getUnits()->at(a)->build();
			}
			glPopMatrix();

		}

	}

}

void control::buildNeutral() {
	building* building;
	unit* unit;


	QTime time;
	time.start();
	int size = neutral->getBuildings()->size();
	for(int a=0;a<size;a++) {
		building = neutral->getBuildings()->at(a);
		glPushMatrix();
		float y = building->getPosition().getY();
		float x = building->getPosition().getX();
		glTranslatef(x*100,y*100,0);
		if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() == 511) {
			glColor3f(0.3f,0.3f,0.3f);
		}
		else if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 0) {
				glColor3f(0.8f,0.8f,0.8f);
		}
		neutral->getBuildings()->at(a)->build();
		glPopMatrix();
		glColor3f(1.0f,1.0,1.0);
	}
	//cout<<"TOTAL UPDATE TIME"<<time.elapsed()<<endl;
	for(int a=0;a<neutral->getUnits()->size();a++) {
		unit = neutral->getUnits()->at(a);
		glPushMatrix();
		float y = unit->getPosition().getY();
		float x = unit->getPosition().getX();
		glTranslatef(x*100,y*100,0);
		if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 511) {
			if(*player->getFoW()->getFowVector()->at(y)->at(x)->getBits() != 0) {
				glColor3f(0.8f,0.8f,0.8f);
			}
			neutral->getUnits()->at(a)->build();
		}
		glPopMatrix();
	}

}

void control::attemptBuild() {
	if(droneBuilding) {
		glPushMatrix();
		float y = droneBuild->getPosition().getY();
		float x = droneBuild->getPosition().getX();
		glTranslatef(x,y,0);
		droneBuild->build();
		glPopMatrix();
	}

}

/* Singleton class method used for starting up and then returning the current control */
control* control::getInstance() {
     if(NULL == m_pInstance ) {
            m_pInstance = new control();
     }
     return m_pInstance;
}
 
/* destroys the current instance (probably will be used for restart 
   and exit of current game to main menu) 
*/
void control::destroyInstance() {
     delete m_pInstance;
     m_pInstance = NULL;
}
