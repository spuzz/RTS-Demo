#include "attackAbility.h"
#include "sidePanel.h"
#include "control.h"

attackAbility::attackAbility(string image, string name) : ability(image,name) {

}


void attackAbility::use() {

	control* ctrl = control::getInstance();
	ctrl->setDroneBuilding(true);
	
}