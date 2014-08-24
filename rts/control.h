/* Main control class, singleton design patter method used to allow
 * to allow access from all gui.
 */


#pragma once

#include "logging.h"
#include <string>
#include "grid.h"
#include "playerControl.h"
#include "sidePanel.h"
#include "sprite.h"
#include "collisionGrid.h"
#include "quadTree.h"
#include "pathingQueue.h"

using namespace std;

class control {
public:

	//Main Methods

	void buildGrid();
	void buildFog();
	void setUpInitial();
	void playerSelect(float x,float y);
	void playerSelect(point2d* start, point2d* end);
	void determineSelection(float x, float y);
	void determineSelection(point2d* start, point2d* end);
	vector<sprite*> getPlayerSelect();
	void addPlayerBuilding(float x, float y);
	void addPlayerUnit(string name,float x, float y);
	
	void createDroneBuilding(string image, string colour);

	//getters and setters
	void setMainGrid(grid* grd) {maingrid = grd;}
	grid* getMainGrid() {return maingrid;}
	void setSidePanel(sidePanel* sdPanelIn ) {sdPanel = sdPanelIn ; }
	void setDroneBuildPos(float xpoint, float ypoint);
	void setDroneBuilding(bool b) { droneBuilding = b; }
	void setColTree(collisionGrid* tree) { colTree = tree; }

	playerControl* getPlayerControl() { return player; }
	vector<playerControl*> getAIControl() { return ai; }
	bool getDroneBuilding() { return droneBuilding; }
	collisionGrid* getColTree() { return colTree; }
	quadTree* getQuadTree() { return qdTree; }
	vector<point2d> getBuildingPositions();
	vector<point2d*> getBuildingSizes();
	pathingQueue* getPathingQueue() { return pathQueue; }
	// begin running of game
	void go();

	// update functions of all player controls
	void buildPlayer();
	void buildAI();
	void buildNeutral();
	void attemptBuild();

	// Singleton class methods
	static control* getInstance();
    void destroyInstance();


	// diagnostic
	void debug();
	void addQuadTreeLines();

private:
	grid* maingrid;
	int unitId;
	bool droneBuilding;
	// All player controls within game - "player" instance is the 
	// human player using the keyboard input
	playerControl* resource;
	playerControl* player;
	playerControl* neutral;
	vector<playerControl*> ai;
	vector<playerControl*> allPlayerControllers;
	building* droneBuild;
	sidePanel* sdPanel;
	collisionGrid* colTree;
	quadTree* qdTree;
	GLuint square;
	pathingQueue* pathQueue;

	// methods
	QTime logicLock;
	void updateLogic();
	void render();
	// construtor/destructor - these are private as this is a singleton class
    control();
    ~control(){}

	// main instance that is returned for singleton class
    static control* m_pInstance;
};