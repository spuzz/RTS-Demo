
#include "abilityPanel.h"
#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "texLoad.h"
#include "ui_abilitypanel.h"
#include "sidePanel.h"
#include "control.h"

abilityPanel::abilityPanel() : QWidget(),
	ui(new Ui::abilityPanel)
{
	ui->setupUi(this);
	mainLayout = new QGridLayout;
	mainLayout->setContentsMargins(1,1,1,1);
	mainLayout->setSpacing(0);
	setLayout(mainLayout);
	maxSelectWidth = 3;
	maxSelectHeight = 3;

}
void abilityPanel::setup(vector<ability*> spr) {
	abilities = spr;
	// go through currently selected images and delete each pointer
	for(int a=0;a<selectedImages.size();a++) {
		delete selectedImages[a];
	} 
	// clear the vector (pointers are already deleted
	selectedImages.clear();

	// these control the layout of the selected images
	int currentWidth = 1;
	int currentHeight = 1;

	// go through each selected sprite
	for(int a=0;a<spr.size();a++) {

		mainLayout->setAlignment(Qt::AlignTop);
		mainLayout->setHorizontalSpacing(10);
		//mainLayout->setMargin(30);
		QToolButton *p = new QToolButton;
		p->setAutoFillBackground(true);
		p->setIcon(QIcon(spr[a]->getImage().c_str()));
		p->setIconSize(QSize(40,40));
		p->setToolTip("Comment");
		connect(p, SIGNAL(clicked()), this, SLOT(buttonClicked()));
		if(currentWidth > maxSelectWidth) {
			currentWidth = 1;
			currentHeight += 1;
		}
		selectedImages.push_back(p);
		mainLayout->addWidget(selectedImages.back(),currentHeight,currentWidth,Qt::AlignLeft);
		setLayout(mainLayout);
		currentWidth += 1;
	}

	repaint();
}
void abilityPanel::buttonClicked() {
	QToolButton *button = (QToolButton *)sender();
	for(int a=0;a<selectedImages.size();a++) {
		
		if(button == selectedImages[a]) {
			abilities[a]->use();
		}
	}
	

}