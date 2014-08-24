#include "selectionPanel.h"

selectionPanel::selectionPanel() {
	mainLayout = new QGridLayout;
	mainLayout->setContentsMargins(1,1,1,1);
	mainLayout->setHorizontalSpacing(15);
	mainLayout->setVerticalSpacing(0);
	setLayout(mainLayout);
	maxSelectWidth = 4;
}


void selectionPanel::updateInfo(vector<sprite*> selection) {
	for(int a=0;a<bars.size();a++) {
		bars[a]->setValue(selection[a]->getHealth());
	} 
}

void selectionPanel::setNewSelection(vector<sprite*> selection) {
	// go through currently selected images and delete each pointer
	for(int a=0;a<selectedImages.size();a++) {
		delete selectedImages[a];
		delete bars[a];
	} 
	// clear the vector (pointers are already deleted
	selectedImages.clear();
	bars.clear();
	// these control the layout of the selected images
	int currentWidth = 1;
	int currentHeight = 1;

	// go through each selected sprite
	for(int a=0;a<selection.size();a++) {
		QProgressBar* bar = new QProgressBar();
		bar->setMaximum(selection[a]->getMaxHealth());
		bar->setMinimum(0);
		bar->setValue(selection[a]->getHealth());
		//bar->setVisible(true);
		//bar->setStyle(new QPlastiqueStyle() );
		bar->setTextVisible(false);
		bar->setFormat("%v%m");
		bar->setMaximumWidth(30);
		bar->setMaximumHeight(10);
		mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		//mainLayout->setAlignment(Qt::AlignLeft);
		//mainLayout->setAlignment(Qt::Alignment(2));


		QToolButton *p = new QToolButton;
		p->setAutoFillBackground(true);
		p->setIcon(QIcon(("Data/" + selection[a]->getImage()).c_str()));
		p->setIconSize(QSize(30,30));
		p->setToolTip("Comment");
		p->setMaximumWidth(30);
		p->setMaximumHeight(this->height()/8);

		if(currentWidth > maxSelectWidth) {
			currentWidth = 1;
			currentHeight += 1;
		}
		selectedImages.push_back(p);
		bars.push_back(bar);
		mainLayout->addWidget(selectedImages.back(),currentHeight*2,currentWidth,Qt::AlignLeft);
		mainLayout->addWidget(bar,currentHeight*2+1,currentWidth,Qt::AlignLeft);
		setLayout(mainLayout);
		currentWidth += 1;
	}

	repaint();
}