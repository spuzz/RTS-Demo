#pragma once

#include "ability.h"

class trainAbility : public ability {

public:
	//construtor
	trainAbility(string image, string name,string buildName);

	//main methods
	void use();
private:
	string buildName;
};