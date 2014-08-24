#include "trainAbility.h"
#include "sidePanel.h"
#include "control.h"

trainAbility::trainAbility(string image, string name,string bName) : ability(image,name) {
	buildName = bName;
}


void trainAbility::use() {
	logging::log(logging::FINEST,"Train creation ability used");
	control* ctrl = control::getInstance();
	ctrl->getPlayerSelect()[0]->useBuild(buildName);
	//ctrl->addPlayerUnit(name,ctrl->getPlayerSelect()[0]->getPosition().getX()*100,(ctrl->getPlayerSelect()[0]->getPosition().getY()-1)*100);
}