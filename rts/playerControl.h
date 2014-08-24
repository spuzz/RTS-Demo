#pragma once


#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "texLoad.h"
#include "sprite.h"
#include <map>
#include "SOIL.h"
#include <QtGui>
#include "unit.h"
#include "building.h"
#include "fogofwar.h"
#include "group.h"

using namespace std;

class playerControl {
public:
	// Constructors

	playerControl();
	playerControl(string colour,map<string,map<string,string>> spriteMap, map<string,map<string,map<string,string>>> abilityMap,int width, int height);

	// Main Public Methods
	void update(bool neutral = false);
	void updateControl(sprite* spr);
	void selectFeature();
	void selectGroup();
	void switchSelectToGroup();
	void createGroup();
	void moveSelected(point2d target,bool attackMove);
	void updateGroupPath(unit* lead, aStar* completedPath);
	sprite* determineClosest(point2d target);
	void addBuilding(string name, float x, float y);
	void addUnit(string name, float x, float y);
	void setupFow(int width, int height);
	void textureMap();
	void trySelect(float x, float y);
	void trySelect(point2d* start, point2d* end);
	void updateFow();

	// Getters and setters
	void setResources(int w,int g,int i,int p);

	void setWood(int w) {wood = w; }
	void setGold(int g) {gold = g; }
	void setIron(int i) {iron = i; }
	void setPop(int p) {population = p; }

	void increaseWood(int w) {wood += w; }
	void increaseGold(int g) {gold += g; }
	void increaseIron(int i) {iron += i; }
	void increasePop(int p) {population += p; }

	void decreaseWood(int w) {wood -= w; }
	void decreaseGold(int g) {gold -= g; }
	void decreaseIron(int i) {iron -= i; }
	void decreasePop(int p) {population -= p; }

	int getWood() {return wood; }
	int getGold() {return wood; }
	int getIron() {return wood; }
	int getPop() {return wood; }
	vector<int> getResources();
	bool checkResources();

	vector<building*>* getBuildings() {return &playerBuildings; }
	vector<unit*>* getUnits() {return &playerUnits; }
	vector<sprite*> getSelected() {return selected; }
	string getColour() {return colour; }
	GLuint getTerrainTexture(string key);
	fogofwar* getFoW() { return fowControl; }

	static int unitId;

	static bool NeedsRemoval(const group & grp)
	{ 
		if(const_cast<group*>(&grp)->getUnits()->size() == 0) {
			return true;
		}
		return false;
	}

private:
	map<string,vector<sprite*>> groups;
	vector<building*> playerBuildings;
	vector<unit*> playerUnits;
	vector<sprite*> selected;
	vector<group> groupMoveSelections;
	map<string,map<string,string>> spriteMap;
	map<string,map<string,map<string,string>>> abilityMap;
	GLuint text[2];
	GLuint terrainText[2];
	map<float,GLuint> texture;
	map<string,GLuint> terrainTexture;
	building* newBuilding;
	string colour;

	fogofwar* fowControl;

	int gold;
	int wood;
	int iron;
	int population;

	int totalTime;
};