/* Class containing individual info from xml to retrieve image from sprite sheet */
#pragma once 

#include <string>
using namespace std;

class spriteInfo
{
public:
	// Constructor and Destructor
	spriteInfo();
	~spriteInfo();

	// Setters and Getters
	string getName() { return name; }
	string getSpriteSheetName() { return spriteSheetName; }
	int getXOffSet() { return xOffSet; }
	int getYOffSet() { return yOffSet; }
	int getMapValue() { return mapValue; }
	int getMovable() { return movable; }

	void setName(string n) {name = n; }
	void setSpriteSheetName(string n) { spriteSheetName = n; }
	void setXOffSet(int x) { xOffSet = x; }
	void setYOffSet(int y) { yOffSet = y; }
	void setMapValue(int v) { mapValue = v; }
	void setMovable(int v) { movable = v; }

private:
	string name;
	string spriteSheetName;
	int xOffSet, yOffSet;
	int mapValue;
	bool movable;

};