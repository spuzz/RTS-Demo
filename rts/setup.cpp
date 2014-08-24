#include "setup.h"

setup::setup() {

}

setup::setup(string mapFile) {
	mainGrid->createGrid(mapFile);
}

void setup::build() {
	//mainGrid->buildGrid();
}

void setup::createGrid(string mapFile) {
	mainGrid = new grid();
	mainGrid->createGrid(mapFile);
}
