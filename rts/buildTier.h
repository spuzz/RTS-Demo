#pragma once

#include "ability.h"

class buildTier : public ability {

public:

	//constructor
	buildTier();
	buildTier(vector<ability*> abilities,string image, string name);

	//main methods
	void use();
	//getters and setters
	vector<ability*> getBuildings() { return buildings; }
	
	void setBuildings(vector<ability*> b) { buildings = b; }
	void addBuilding(ability* s) { buildings.push_back(s); }


private:
	vector<ability*> buildings;
};