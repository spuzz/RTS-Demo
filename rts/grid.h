#pragma once

#include "tile.h"
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "fogofwar.h"
#include "tileMapParser.h"

using namespace std;

class grid {

public:
	// constructors
	grid();
	grid(string mapfile);

	// public methods
	void createGrid(string mapfile);
	void buildGrid(fogofwar* fowControl);
	void showGrid();
	// Setter/getters
	vector<vector<tile*>>* getGrid() { return &mainGrid; }
	vector<vector<tile*>>* getTerrainGrid() { return &terrainGrid; }
	GLuint getTexture(float key);
	GLuint getTerrainTexture(float key);
	float getWidth() { return width; }
	float getHeight() { return height; }
	
private:
	// private variables
	GLuint text[2];
	GLuint terrainText[2];
	vector<vector<vector<tile*>>> layers;
	vector<vector<tile*>> mainGrid;
	vector<vector<tile*>> terrainGrid;
	map<float,GLuint> texture;
	map<float,GLuint> terrainTexture;
	FILE *filein, *collin;
	float width,height;
	tile* newTile;
	tile* terrainTile;
	tileMapParser tileInfo;
	// private methods
	
	vector<string> tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ");

	void readFile();
	void textureMap(tileMapParser tileInfo);
	string createWidthString(float size);

};