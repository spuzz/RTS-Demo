#pragma once

#include "sprite.h"
#include "trainAbility.h"
#include <map>
#include <QtGui>

class building : public sprite {

public:
	//constructors
	building();

	//main methods
	string update();
	void setup(map<string,string> xmlValues);
	void createAbilities(map<string,map<string,string>> xmlValues);
	void useBuild(string name);
	void updateTiles();
	//setters and getters
	void setHealth(int h) { health = h; }
	void hit(int ouch) { health -= ouch; cout<<"I GOT HIT "<<health<<endl; }
	void heal(int heal) { health += heal; }
	void setMaxHealth(int h) { maxHealth = h; }
	void setDamage(int d) { damage = d; }
	void setArmor(int a) { armor = a; }
	void setRange(int r) { range = r; }

	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	int getDamage() {return damage; }
	int getArmor() { return armor; }
	int getRange() { return range; }

protected:
	string buildObject;
	int damage;
	int armor;
	int range;
	bool working;
	QTime timer;

private:

};