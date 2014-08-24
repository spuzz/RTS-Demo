#include "logging.h"
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "QtMainGame.h"
#include "gameMainWindow.h"

int main(int argc, char *argv[])
{
	logging::open();
	logging::log(logging::BASIC,"Application has started");


    QApplication app(argc, argv);
	
	MainWindow window;
	window.setAutoFillBackground(true);
	window.setVisible(true);
	//setMargin(10,10,10,10);
	app.setStyleSheet("border: 2px solid beige");
	QPalette palette;
	palette.setBrush(window.backgroundRole(), QBrush(QImage("Data/lifebackground.png")));

	window.setPalette(palette);
	window.resize(1200,600);
	window.show();
	window.updateGeom();
    window.showMaximized();
    return app.exec();
}
