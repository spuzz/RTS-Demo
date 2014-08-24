#pragma once

#include <iostream>
#include <string>
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <map>
using namespace std;



class logging {



public:
	
	static enum level { BASIC, INFO, FINE, FINEST };
	static level AllLevel;
	static void open();
	static void destroy();
	static void log(level lvl, string txt);
	static void log(level lvl, float txt);
	static void log(level lvl, int txt);
	static void setLevel(level lvl);

private:
};






