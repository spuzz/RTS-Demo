#include "ability.h"
#include "buildTier.h"
#include "trainAbility.h"
#include "buildAbility.h"
#include "logging.h"

ability::ability(string im, string nm) {
	image = im;
	name = nm;
}

void ability::use() {
}

ability* ability::create(string type,string image,map<string,string> attr) {
	logging::log(logging::FINEST,"Creating ability");
    if ( type == "buildTier" ) {
		vector<ability*> tierBuildings;
		for ( map<string,string>::const_iterator iter = attr.begin();
			iter != attr.end(); ++iter ) {
				if(iter->first.find("building") == 0) {
					map<string,string> tmp;
					ability* ab = ability::create("buildAbility",attr["image"] + ".png",tmp);
					tierBuildings.push_back(ab);
				}
		}
		return new buildTier(tierBuildings,image,type);
	}
    if ( type == "trainAbility" ) {
		return new trainAbility(image,type,attr["buildName"]);
	}
	if ( type == "attackAbility" ) {
		return new trainAbility(image,type,attr["buildName"]);
	}
	if ( type == "buildAbility" ) {
		return new buildAbility(image,"building");
	}
    return NULL;
}