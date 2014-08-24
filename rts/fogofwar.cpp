#include "fogofwar.h"

// Shape masks which are used to perform bitwise AND operater on fog tiles to determine visability
unsigned short circle_mask[NUM_FOW_RADII][FOW_MAX_RADIUS_LENGTH * FOW_MAX_RADIUS_LENGTH] =
	{
		// radius 3
		{
			fow_all,fow_all,fow_CNW,fow_NNN,fow_CNE,fow_all,fow_all,
				fow_all,fow_CNW,fow_JNW,fow_non,fow_JNE,fow_CNE,fow_all,
				fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
				fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
				fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
				fow_all,fow_CSW,fow_JSW,fow_non,fow_JSE,fow_CSE,fow_all,
				fow_all,fow_all,fow_CSW,fow_SSS,fow_CSE,fow_all,fow_all,
		},
		// radius 4
		{
			fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,
				fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
				fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
				fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
				fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
				fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
				fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
				fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
				fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,
			},
			// radius 5
			{
				fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_NNN,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,
					fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
					fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
					fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
					fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
					fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
					fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
					fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
					fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
					fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
					fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_SSS,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,
			},
			// radius 6
			{
				fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_NNN,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,
					fow_all,fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,fow_all,
					fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
					fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
					fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
					fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
					fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
					fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
					fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
					fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
					fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
					fow_all,fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,fow_all,
					fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_SSS,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,
				},
				// radius 7
				{
					fow_all,fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_NNN,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
						fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
						fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
						fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
						fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
						fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
						fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_SSS,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,fow_all,
				},
				// radius 8
				{
					fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_NNN,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
						fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
						fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
						fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
						fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
						fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
						fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
						fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,
						fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_SSS,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,
					},
					// radius 9
					{
						fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_NNN,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,
							fow_all,fow_all,fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_JNW,fow_non,fow_non,fow_non,fow_JNE,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,fow_all,fow_all,
							fow_all,fow_all,fow_all,fow_CNW,fow_NNN,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_NNN,fow_CNE,fow_all,fow_all,fow_all,
							fow_all,fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,fow_all,
							fow_all,fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,fow_all,
							fow_all,fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,fow_all,
							fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
							fow_CNW,fow_JNW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JNE,fow_CNE,
							fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
							fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
							fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,
							fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,
							fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,
							fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,
							fow_all,fow_all,fow_WWW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_EEE,fow_all,fow_all,
							fow_all,fow_all,fow_CSW,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_CSE,fow_all,fow_all,
							fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_JSW,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_non,fow_JSE,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,
							fow_all,fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_JSW,fow_non,fow_non,fow_non,fow_JSE,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,fow_all,
							fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_CSW,fow_SSS,fow_SSS,fow_SSS,fow_CSE,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,fow_all,
					}
};


fogofwar::fogofwar() {
	
}

fogofwar::fogofwar(int w, int h, int fogDetail) {
	width = w;
	height = h;
	int totalEntries = fogDetail;
	// Create grid
	fowTileGrid = new vector<vector<fowTile*>*>();
	for(int a=0;a<width;a++) {
		fowTileGrid->push_back(new vector<fowTile*>());
		for(int b=0;b<height;b++) {
			fowTileGrid->at(a)->push_back(new fowTile());
		}
	}
	// vector containing different images  dependant on visibility of tile
	vector<signed char> fow_frame_table;

	for (int i = 0; i < totalEntries; i++)
	{
		fow_frame_table.push_back(-1);
	}
	fow_frame_table[0x5F]   = 0;
	fow_frame_table[0xB]    = 1;
	fow_frame_table[0x7]    = 2;
}

fogofwar::~fogofwar() {
	delete fowTileGrid;
}

// Adds a unit/building vision to the grid
void fogofwar::addVision(int xLoc, int yLoc,int radius) {
	int tableSize = (radius*2) +1;
	int totalTableEntires = tableSize * tableSize;
	vector<fowTile*> localvector;
	int tile_counter    = 0;
	for (int y = yLoc - (tableSize / 2);
		y <= (yLoc + (tableSize / 2));
		y++)
	{
		for (int x = xLoc - (tableSize / 2);
			x <= (xLoc + (tableSize / 2));
			x++)
		{
			if(y >= 0 && y < height && x >= 0 && x < width) {
				localvector.push_back(fowTileGrid->at(y)->at(x));
			}
			else {
				localvector.push_back(NULL);
			}
		}
	}

	const unsigned short *  mask    = &circle_mask[radius - FOW_RADIUS_MIN][0];
	unsigned short* tmp;
	for (int i = 0; i < totalTableEntires; i++)
	{
		if  (localvector.at(i))
		{
			
			tmp = localvector.at(i)->getBits();
			*tmp &= *mask;
			localvector.at(i)->setBits(tmp);
		}

		mask++;
	}
}

// Cleans up the grid for an update
void fogofwar::clear() {
	for(int a=0;a<fowTileGrid->size();a++) {
		for(int b=0;b<fowTileGrid->at(0)->size();b++) {
			fowTileGrid->at(a)->at(b)->clear();
		}
	}
}


void fogofwar::fowDiagnostic() {
	for(int a=0;a<fowTileGrid->size();a++) {
		for(int b=0;b<fowTileGrid->at(0)->size();b++) {
			//cout<<fowTileGrid->at(a)->at(b)->getBits()<<" AT "<<a<<" "<<b<<endl;
			if(*fowTileGrid->at(a)->at(b)->getBits() != 511) {
				cout<<"Found vision at: "<<a<<" "<<b<<endl;
				cout<<fowTileGrid->at(a)->at(b)->getBits()<<endl;
			}
		}
	}
}