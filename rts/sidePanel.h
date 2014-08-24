/*
	GUI class for side panel. Current usage is for viewing unit/building
	selection and selection order buttons.
*/

#pragma once

#include <QtGui>
#include "sprite.h"
#include "selectionPanel.h"
#include "abilityPanel.h"
#include "ability.h"
#include "infoPanel.h"

class sidePanel : public QWidget {

public:

	void setUp();
	QGridLayout *mainLayout;
	void setNewSelection(vector<sprite*> select);
	void setNewAbilities(vector<ability*> select);
	void updateInfo(vector<sprite*> selection);
	// Singleton class methods
	static sidePanel* getInstance();
    void destroyInstance();
private:
	sidePanel();
	~sidePanel(){}
	abilityPanel* ap;
	selectionPanel* sp;
	infoPanel* ip;
    static sidePanel* m_pInstance;
};