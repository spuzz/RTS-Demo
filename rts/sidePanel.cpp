#include "sidePanel.h"
#include "abilityPanel.h"

sidePanel* sidePanel::m_pInstance = NULL;

sidePanel::sidePanel() {

}


void sidePanel::setUp() {
	mainLayout = new QGridLayout;
	mainLayout->setContentsMargins(1,1,1,1);
	mainLayout->setSpacing(0);
	mainLayout->setVerticalSpacing(20);
	mainLayout->setMargin(20);
	mainLayout->setAlignment(Qt::Alignment(0));
	sp = new selectionPanel();
	ap = new abilityPanel();
	ip = new infoPanel();
	ip->setMaximumHeight(this->height()/3);
	ip->setMinimumHeight(this->height()/3);
	ap->setMaximumHeight(this->height()/3);
	ap->setMinimumHeight(this->height()/3);
	mainLayout->addWidget(ip);
	mainLayout->addWidget(sp);
	mainLayout->addWidget(ap);
	setLayout(mainLayout);
}

void sidePanel::setNewAbilities(vector<ability*> selection) {
	ap->setup(selection);
}

void sidePanel::setNewSelection(vector<sprite*> selection) {
	// update selection panel with selected units
	sp->setNewSelection(selection);
	ip->setNewSelection(selection);
	setLayout(mainLayout);
	if(selection.size() > 0) {
		// update ability panel with unit 0
		ap->setup(selection[0]->getAbilties());
	}
	else {
		// if no units clear ability panel
		vector<ability*> tmp;
		ap->setup(tmp);
	}
}

void sidePanel::updateInfo(vector<sprite*> selection) {
	sp->updateInfo(selection);
}

/* Singleton class method used for starting up and then returning the sidePanel */
sidePanel* sidePanel::getInstance() {
     if(NULL == m_pInstance ) {
            m_pInstance = new sidePanel();
     }
     return m_pInstance;
}
 
/* destroys the current instance (probably will be used for restart 
   and exit of current game) 
*/
void sidePanel::destroyInstance() {
     delete m_pInstance;
     m_pInstance = NULL;
}