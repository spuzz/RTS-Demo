#pragma once

#include <vector>
#include "fowTile.h"
#include "logging.h"
#include <string>

#define	FOW_BIT_NW				(1 << 0)
#define	FOW_BIT_N				(1 << 1)
#define	FOW_BIT_NE				(1 << 2)
#define	FOW_BIT_W				(1 << 3)
#define	FOW_BIT_C				(1 << 4)
#define	FOW_BIT_E				(1 << 5)
#define	FOW_BIT_SW				(1 << 6)
#define	FOW_BIT_S				(1 << 7)
#define	FOW_BIT_SE				(1 << 8)

// these defines are all 7 chars to make it easier to read the circle masks
#define	fow_non					0
#define	fow_all					(FOW_BIT_NW | FOW_BIT_N | FOW_BIT_NE | FOW_BIT_W | FOW_BIT_C | FOW_BIT_E | FOW_BIT_SW | FOW_BIT_S | FOW_BIT_SE)
#define	NUM_FOW_ENTRIES			fow_all

// straights
#define	fow_EEE					(FOW_BIT_SE | FOW_BIT_E | FOW_BIT_NE)
#define	fow_NNN					(FOW_BIT_NE | FOW_BIT_N | FOW_BIT_NW)
#define	fow_WWW					(FOW_BIT_NW | FOW_BIT_W | FOW_BIT_SW)
#define	fow_SSS					(FOW_BIT_SW | FOW_BIT_S | FOW_BIT_SE)

// corners
#define	fow_CNE					(FOW_BIT_E | FOW_BIT_NE | FOW_BIT_N | FOW_BIT_NW | FOW_BIT_C | FOW_BIT_SE)
#define	fow_CNW					(FOW_BIT_N | FOW_BIT_NW | FOW_BIT_W | FOW_BIT_SW | FOW_BIT_C | FOW_BIT_NE)
#define	fow_CSW					(FOW_BIT_W | FOW_BIT_SW | FOW_BIT_S | FOW_BIT_NW | FOW_BIT_C | FOW_BIT_SE)
#define	fow_CSE					(FOW_BIT_S | FOW_BIT_SE | FOW_BIT_E | FOW_BIT_NE | FOW_BIT_C | FOW_BIT_SW)

// joins
#define	fow_JNE					(FOW_BIT_E | FOW_BIT_NE | FOW_BIT_N)
#define	fow_JNW					(FOW_BIT_N | FOW_BIT_NW | FOW_BIT_W)
#define	fow_JSW					(FOW_BIT_W | FOW_BIT_SW | FOW_BIT_S)
#define	fow_JSE					(FOW_BIT_S | FOW_BIT_SE | FOW_BIT_E)

#define	FOW_RADIUS_MIN			3
#define	FOW_RADIUS_MAX			9
#define	NUM_FOW_RADII			((FOW_RADIUS_MAX - FOW_RADIUS_MIN) + 1)

#define	FOW_MAX_RADIUS_LENGTH	((FOW_RADIUS_MAX * 2) + 1)

using namespace std;
/* creates and controls the fog of war coverage */
class fogofwar {

public:
	// Constructors and Destructors
	fogofwar();
	fogofwar::fogofwar(int width, int height, int fogDetail = 512);
	~fogofwar();

	// Main methods
	void clear();
	void addVision(int x, int y, int radius = 3);
	// Setters and getters

	vector<vector<fowTile*>*>* getFowVector() { return fowTileGrid; }
	// Diagnostic
	void fowDiagnostic();

private:
	// Private variables
	vector<vector<fowTile*>*>* fowTileGrid;
	int width,height;
	// private methods
	
};