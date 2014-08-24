#include "gameMainWindow.h"

gameMainWindow::gameMainWindow() {

}

void gameMainWindow::start() {
	
	gameWidget = new QtMainGame;
	//gameWidget->show();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(gameWidget);
	setLayout(mainLayout);
}