#include "infoPanel.h"

infoPanel::infoPanel() {
	mainLayout = new QGridLayout;
	mainLayout->setContentsMargins(1,1,1,1);
	mainLayout->setSpacing(0);
	setLayout(mainLayout);
	maxSelectWidth = 2;
}


void infoPanel::updateInfo(vector<sprite*> selection) {
}

void infoPanel::setNewSelection(vector<sprite*> selection) {
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setHorizontalSpacing(0);
	//mainLayout->setMargin(30);
	//mainLayout->setAlignment(Qt::Alignment(0));


	QToolButton *p = new QToolButton;
	p->setAutoFillBackground(true);
	p->setIcon(QIcon("Data/old.bmp"));
	p->setIconSize(QSize(150,150));
	//p->setMaximumWidth(40);
	//p->setMaximumHeight(40);
	mainLayout->addWidget(p,0,0,Qt::AlignLeft);
}