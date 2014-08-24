#pragma once
#ifndef abilityPanel_H
#define abilityPanel_H

#include <QtGui>
#include "sprite.h"

namespace Ui {
    class abilityPanel;
} // namespace Ui

using namespace std;

class abilityPanel : public QWidget {
	Q_OBJECT
public:
	//constructors
	abilityPanel();

	//main methods
	void setup(vector<ability*> spr);
	//getters and setters

protected slots:
	void buttonClicked();
	
signals:
	void clicked();

private:
	vector<QToolButton*> selectedImages;
	vector<ability*> abilities;
	QGridLayout *mainLayout;
	Ui::abilityPanel *ui;

	int maxSelectWidth;
	int maxSelectHeight;
};

#endif // abilityPanel_H