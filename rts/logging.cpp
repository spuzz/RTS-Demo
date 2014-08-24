#include "logging.h"
#include <ctime>
static map<int, char *> mLevelString;
logging::level logging::AllLevel;

void logging::open() {
	freopen("Data/log.txt", "w", stdout);

	logging::setLevel(FINE);
	mLevelString[BASIC] = "BASIC";
	mLevelString[INFO] = "INFO";
	mLevelString[FINE] = "FINE";
	mLevelString[FINEST] = "FINEST";
}

void logging::destroy() {

}

void logging::log(level lvl, string txt) {
	if(lvl > logging::AllLevel) {
		// Only output messages equal to or below log level
		return;
	}
    struct tm *ptr;
    time_t lt;
    char str[80];

    lt = time(NULL);
    ptr = localtime(&lt);
	strftime(str,100,"%x %X",ptr);
	cout << str
		 << " "
		 << mLevelString[lvl]
		 << ": "
		 << txt
		 << endl;
}

void logging::log(level lvl, float txt) {
	if(lvl > logging::AllLevel) {
		// Only output messages equal to or below log level
		return;
	}
    struct tm *ptr;
    time_t lt;
    char str[80];

    lt = time(NULL);
    ptr = localtime(&lt);
	strftime(str,100,"%x %X",ptr);
	cout << str
		 << " "
		 << mLevelString[lvl]
		 << ": "
		 << txt
		 << endl;
}

void logging::log(level lvl, int txt) {
	if(lvl > logging::AllLevel) {
		// Only output messages equal to or below log level
		return;
	}
    struct tm *ptr;
    time_t lt;
    char str[80];

    lt = time(NULL);
    ptr = localtime(&lt);
	strftime(str,100,"%x %X",ptr);
	cout << str
		 << " "
		 << mLevelString[lvl]
		 << ": "
		 << txt
		 << endl;
}

void logging::setLevel(level lvl) {
	 AllLevel = lvl;
}