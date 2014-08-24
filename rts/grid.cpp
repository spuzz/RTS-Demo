#include "grid.h"
#include "texLoad.h"
#include <png.h>
#include "SOIL.h"
#include "logging.h"
#include "tileMapParser.h"
#define TEXTURE_LOAD_ERROR 0

grid::grid() {
}

grid::grid(string mapFile) {
	// build grid from constructor
	createGrid(mapFile);
}


// This desperatly needs redoing
void grid::createGrid(string mapFile) {
	logging::log(logging::FINE,"Creating Grid from file");
	
	string configFile="Data/Textures/Tiles/TileMap.xml"; // stat file. Get ambigious segfault otherwise.
	tileInfo.readSpriteConfigFile(configFile);
	textureMap(tileInfo);
	char oneline[255];
	filein = fopen(mapFile.c_str(), "rt");				// File To Load World Data From
	fgets(oneline,255,filein);
	sscanf(oneline, "%f x %f\n", &width,&height);
	sscanf(oneline, "%f x %f\n", &width,&height);
	vector<string> test;
	// for each tile in map file read value
	for(int a=0;a<height;a++) {
		vector<tile*> tiles;
		vector<tile*> terrain;
		test.clear();
		fgets(oneline,255,filein);
		int len = strlen(oneline);
		if( oneline[len-1] == '\n' )
			oneline[len-1] = 0;
		test = tokenize(oneline,test);
		for(int b=0;b<test.size();b++) {
			cout<<test.size()<<" "<<test.at(b)<<endl;
			newTile = new tile();
			newTile->createTexture(getTexture(atof(test[b].c_str())),tileInfo.getSpriteMap().at(test.at(b))->getSpriteSheetName());
			//if(test[b].find("2") != string::npos) {

			//	newTile->createTexture(getTexture(0),"Data/water.png");
			//}
			//else {
			//	newTile->createTexture(getTexture(atof(test[b].c_str())),"Data/water.png");
			//}
			newTile->setSize(100,100);
			newTile->createDisplayList();
			tiles.push_back(newTile);
			newTile->setMoveable(tileInfo.getSpriteMap().at(test.at(b))->getMovable());

			//if(test[b].find("2") != string::npos) {
			//	terrainTile = new tile();
			//	terrainTile->createTexture(getTexture(atof(test[b].c_str())),"Data/water.png");
			//	terrainTile->setSize(100,100);
			//	terrainTile->createDisplayList();
			//	terrain.push_back(terrainTile);
			//}
			//else if(test[b].find("3") != string::npos) {
			//	terrainTile = new tile();
			//	terrainTile->createTexture(getTexture(atof(test[b].c_str())),"Data/wall.png");
			//	terrainTile->setSize(100,100);
			//	terrainTile->createDisplayList();
			//	terrain.push_back(terrainTile);
			//}
			//else {
				terrain.push_back(NULL);
			//}

		}
		mainGrid.push_back(tiles);
		terrainGrid.push_back(terrain);
	}
	layers.push_back(mainGrid);
	layers.push_back(terrainGrid);
	fclose(filein);
}

GLuint grid::getTexture(float key) {
	// get texture for individual tile from map file value
	return texture[key];
}

GLuint grid::getTerrainTexture(float key) {
	// get texture for individual tile from map file value
	return terrainTexture[key];
}

void grid::textureMap(tileMapParser tileInfo) {
	// build map object of texture files for comparison with map text file
	//texture[0] = texLoad::LoadGLTextures("Data/tree.png",text[0]);
	//texture[0] = texLoad::LoadGLTextures("Data/GrassTexture.bmp",text[0]);
	//texture[1] = texLoad::LoadGLTextures("Data/water.png",text[1]);
	for(int a=0;a<tileInfo.getSpriteMap().size();a++) {
		stringstream ss;//create a stringstream
		ss << a;//add number to the stream
		cout<<tileInfo.getSpriteMap().at(ss.str())->getSpriteSheetName().c_str()<<endl;
		texture[a] = SOIL_load_OGL_texture
		(
		tileInfo.getSpriteMap().at(ss.str())->getSpriteSheetName().c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	}
	//texture[0] = SOIL_load_OGL_texture
	//	(
	//	"Data/GrassTexture.bmp",
	//	SOIL_LOAD_RGBA,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	//	);

	//texture[1] = SOIL_load_OGL_texture
	//	(
	//	"Data/water.png",
	//	SOIL_LOAD_RGBA,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	//	);
	//texture[2] = SOIL_load_OGL_texture
	//	(
	//	"Data/tree.png",
	//	SOIL_LOAD_RGBA,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	//	);
	//texture[3] = SOIL_load_OGL_texture
	//	(
	//	"Data/wall.png",
	//	SOIL_LOAD_RGBA,
	//	SOIL_CREATE_NEW_ID,
	//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	//	);
}

void grid::buildGrid(fogofwar* fowControl) {
	// show low level terrain features
	for(int a=mainGrid.size()-1;a>=0;a--) {
		for(int b=0;b<mainGrid[a].size();b++) {
			glPushMatrix();
			glTranslatef(b*100,a*100,0);
			if(*fowControl->getFowVector()->at(a)->at(b)->getBits() == 511) {
				glColor3f(0.6f,0.6f,0.6f);
				
			}
			else if(*fowControl->getFowVector()->at(a)->at(b)->getBits() != 0) {
				glColor3f(0.8f,0.8f,0.8f);
			}
			layers[0][a][b]->build();
			glPopMatrix();
			glColor3f(1.0f,1.0f,1.0f);

		}
	}
}


vector<string> grid::tokenize(const string& str,vector<string>& tokens,const string& delimiters) {
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
	return tokens;
}
