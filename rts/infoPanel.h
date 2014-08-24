#pragma once
#include <QtGui>
#include "sprite.h"
#include <vector>

using namespace std;
class infoPanel : public QWidget {

public:
	infoPanel();
	void setNewSelection(vector<sprite*> select);
	void updateInfo(vector<sprite*> selection);
private:
	QGridLayout *mainLayout;
	vector<QToolButton*> selectedImages;
	int maxSelectWidth;
	int maxSelectHeight;
	vector<QProgressBar*> bars;
};