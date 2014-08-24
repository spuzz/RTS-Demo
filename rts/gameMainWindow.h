#pragma once

#include "mainwindow.h"
#include "QtMainGame.h"
#include <QtGUI>

class gameMainWindow : public MainWindow {

public:
	gameMainWindow();
	void start();
private:
	QtMainGame* gameWidget;
};