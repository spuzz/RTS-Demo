#include "buildAbility.h"
#include "sidePanel.h"
#include "control.h"

buildAbility::buildAbility(string image, string name) : ability(image,name) {

}


void buildAbility::use() {

	control* ctrl = control::getInstance();
	ctrl->setDroneBuilding(true);
	
}