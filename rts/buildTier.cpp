#include "buildTier.h"
#include "sidePanel.h"

buildTier::buildTier(vector<ability*> abilities,string image, string name) : ability(image,name) {
	setBuildings(abilities);
}


void buildTier::use() {
	logging::log(logging::FINEST,"Building creation ability used");
	sidePanel* sd = sidePanel::getInstance();
	sd->setNewAbilities(getBuildings());
}