#pragma once


#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"
#include "texLoad.h"
#include "ability.h"
#include "logging.h"

using namespace std;


class sprite {


public:
	
	// constructors
	sprite();

	//public methods
	void createTexture(GLuint tex,string img);
	void createDisplayList();
	void build();
	virtual void updateTiles();
	virtual string update();
	virtual void hit(int damage);
	virtual void setup();
	virtual void useBuild(string name);
	virtual void updateGoal(point2d* tar, bool att) {};
	virtual void move() {};
	virtual void updatePathAdjustment(float x, float y) { xPathAdj = x; yPathAdj = y;};
	//getters and setters
	string getType() { return spriteType; }
	string getModel() { return model; }
	bool getMovable() { return movable; }
	bool getShow() { return show; }
	float get3Dheight() { return h3d; }
	point2d getPosition() { return location; }
	point2d* getDirection() { return direction; }
	point2d* getSize() { return size; }
	point2d* getVelocity() { return velocity; }
	point2d* getTarget() { return target; }
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	string getImage() { return textureString; }
	int getUnitId() { return unitId; }
	string getColour() {return colour; }
	int getDamage() {return damage; }
	int getArmor() { return armor; }
	int getRange() { return range; }
	vector<ability*> getAbilties() { return abilities; }
	vector<point2d*> getTiles() { return tiles; }
	sprite* getLeader() { return leader; }
	virtual bool getEndPath();

	void setTarget(point2d* t) { target = t; targetChanged = true; }
	void setImage(string img) { textureString = img; }
	void setMoveable(bool b) { movable = b; }
	void setType(string t) { spriteType = t; }
	void setModel(string m) { model = m; }
	void setShow(bool s) { show = s; }
	void set3Dheight(float f) { h3d = f; }
	void setPosition(float xIn, float yIn);
	void setDirection(float xIn, float yIn);
	void setSize(float xIn, float yIn);
	void setVelocity(float xIn, float yIn);
	void setUnitId(int id) {unitId = id; }
	void setColour(string c) {colour = c; }
	void setHealth(int h) { health = h; }
	void heal(int heal) { health += heal; }
	void setMaxHealth(int h) { maxHealth = h; }
	void setDamage(int d) { damage = d; }
	void setArmor(int a) { armor = a; }
	void setRange(int r) { range = r; }
	void setLeader(sprite* spr) { leader = spr; }

	void addAbility(ability* a) {abilities.push_back(a); }

	friend bool operator== (sprite spr1, sprite spr2)
	{
		if(spr1.getUnitId() == spr2.getUnitId()) {
				return true;
		} else {
			return false;
		}
	}


protected:
	// private variables
	vector<point2d*> tiles;
	enum status { IDLE, EXPLORE, ATTACK, ATTACKMOVE, MOVE };
	
	sprite* leader;
	string spriteType;
	int layer;	// layer that sprite resides in (tile,terrain/building, unit)
	int unitId;
	string colour;
	string textureString;
	bool show;
	bool movable;
	bool changed;
	bool targetChanged;
	float h3d; // image height over tile
	string model;
	string curTexture;
	status unitStatus;
	QBasicTimer* timer;
	point2d location; // map position
	point2d* size;
	point2d* direction; // direction of movement
	point2d* velocity; // movement speed
	point2d* target;
	int health;
	int maxHealth;
	int damage;
	int armor;
	int range;
	int vision;
	// 2 floats to adjust path movement
	float xPathAdj, yPathAdj;
	GLuint texture[1];
	GLuint list;

	vector<ability*> abilities;
	// private methods

};