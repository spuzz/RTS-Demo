#pragma once

#include "ability.h"

class attackAbility : public ability {

public:
	//construtor
	attackAbility(string image, string name);

	//main methods
	void use();
private:

};