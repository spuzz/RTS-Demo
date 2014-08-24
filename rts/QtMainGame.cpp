#include "QtMainGame.h"
#include <QTimer>
#include <QTime>
#include "ui_QtMainGame.h"

using namespace std;



HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values


QtMainGame::QtMainGame(QWidget *parent) : QGLWidget(),
	ui(new Ui::Form)
{
	ui->setupUi(this);
	setMouseTracking(true);
	timerInterval = 20;
	active=TRUE;		// Window Active Flag Set To TRUE By Default
	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
	mousePosition.push_back(0.1f);
	mousePosition.push_back(0.1f);
	curXCam = 0;
	curYCam = 0;
	curXEndCam = 2000;
	curYEndCam = 2000;
	mouseWheel = 0;
	zoomspeed = 300;
	z=-5.0f;			// Depth Into The Screen
	ZOOM = -20.f;
    LightAmbient[0] = 1.0f; LightAmbient[1] = 1.0f; LightAmbient[2] = 1.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightAmbient[1] = 1.0f; LightAmbient[2] = 1.0f; LightAmbient[3] = 1.0f;
	LightPosition[0] = 0.0f; LightAmbient[1] = 0.0f; LightAmbient[2] = 2.0f; LightAmbient[3] = 1.0f;
	makeCurrent();
	m_timer = new QTimer( this );
	connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
	m_timer->start( timerInterval );
}

int QtMainGame::LoadGLTextures()									// Load Bitmaps And Convert To Textures
{		
	//texture[0] = texLoad::LoadGLTextures("Data/Dfloor.bmp",texture[0]);
	return 1;// Return The Status
}

GLvoid QtMainGame::moveScreen()	// Resize And Initialize The GL Window
{
	// Calculate The Aspect Ratio Of The Window
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();
	//glOrtho(adjustedXCam, adjustedXEndCam, curYCam, curYEndCam,0,0);
	//glOrtho(adjustedXCam, adjustedXEndCam, curYCam, curYEndCam,0,0);

    glOrtho(adjustedXCam, adjustedXEndCam, curYCam, curYEndCam, -30, 100);

	//glTranslatef(50, 500, 100);
	
	//glRotaadjustedXCam, adjustedXEndCam, curYCam, curYEndCam,0.0);
	//glRotatef(-6.0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	//glRotatef(25.0, 1,0,0);
	
	makeCurrent();

}
GLvoid QtMainGame::resizeGL(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	glViewport(0,0,width,height);
	// Calculate The Aspect Ratio Of The Window
	widthToHeight = ((float)this->width()/(float)this->height());
	adjustedXEndCam = curXEndCam*widthToHeight;
	adjustedXCam = curXCam*widthToHeight;

}

GLvoid QtMainGame::zoomIn(float x, float y) {
	float xPerc = 0;
	float yPerc = 0;
	xPerc = (x/ width()) *100;
	yPerc = (y/ height()) *100;
	if(curXEndCam - curXCam > 100 && curYEndCam - curYCam > 100) {
		curXCam += (zoomspeed/100)*xPerc;
		adjustedXCam = curXCam*widthToHeight;
		curYCam += (zoomspeed/100)*(100-yPerc);
		curXEndCam -= (zoomspeed/100)*(100-xPerc);
		adjustedXEndCam = curXEndCam*widthToHeight;
		curYEndCam -= (zoomspeed/100)*yPerc;
		
	}
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();
	//gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid QtMainGame::zoomOut(float x, float y) {
	float xPerc = 0;
	float yPerc = 0;

	xPerc = x/ width();
	yPerc = y/ height();
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();
	int newCurXCam = (curXCam - (zoomspeed/2))*widthToHeight;
	int newCurYCam = curYCam - zoomspeed/2;
	int newCurXEndCam = (curXEndCam + (zoomspeed/2))*widthToHeight;
	int newCurYEndCam = curYEndCam + zoomspeed/2;;

	bool maxed = false;
	if(newCurXCam < 0) {
		newCurXEndCam -= newCurXCam;
		newCurXCam = 0;
		if(newCurXEndCam > 6400) {
			newCurXEndCam = 6400;
			maxed = true;
		}
	}
	if(newCurXEndCam > 6400 & maxed != true) {
		newCurXCam += (6400 - newCurXEndCam);
		newCurXEndCam = 6400;
		if(newCurXCam < 0) {
			newCurXCam = 0;
			maxed = true;
		}
	}


	if(newCurYCam < 0 & maxed != true) {
		newCurYEndCam -= newCurYCam;
		newCurYCam = 0;
		if(newCurYEndCam > 6420) {
			newCurYEndCam = 6420;
			maxed = true;
		}
	}
	if(newCurYEndCam > 6420 & maxed != true) {
		newCurYCam += (6420 - newCurYEndCam);
		newCurYEndCam = 6420;
		if(newCurYCam < 0) {
			newCurYCam = 0;
			maxed = true;
		}
	}
	if(maxed != true) {
		adjustedXCam = newCurXCam;
		adjustedXEndCam = newCurXEndCam;
		curXCam = newCurXCam/widthToHeight;
		curYCam = newCurYCam;
		curXEndCam = newCurXEndCam/widthToHeight;;
		curYEndCam = newCurYEndCam;
	}
	//gluOrtho2D(curXCam, curXEndCam, curYCam, curYEndCam);

	glMatrixMode(GL_MODELVIEW);
}

void QtMainGame::getMouseInfo()
{
   static POINT lastMouse = {0,0};
   //Get current mouse position
   GetCursorPos(&lastMouse);

   //Update mouse position
   //mousePosition[0] = 6400*((float(lastMouse.x)/float(width())));
   //mousePosition[1] = 6420 - 6420*((float(lastMouse.y)/float(height())));
   mousePosition[0] = float(lastMouse.x) - screenX;
   mousePosition[1] = float(lastMouse.y) - screenY;
   if(mousePosition[0] > float(mainScreenWidth) - 1) {
	   if(adjustedXEndCam < 6351) {
		   curXEndCam += 50;
		   adjustedXEndCam += 50*widthToHeight;
		   curXCam += 50;
		   adjustedXCam += 50*widthToHeight;
	   }
   }
   else if (mousePosition[0] < 1) {
	   if(adjustedXCam > 49) {
		   curXEndCam -= 50;
		   adjustedXEndCam -= 50*widthToHeight;
		   curXCam -= 50;
		   adjustedXCam -= 50*widthToHeight;
	   }

   }
   if(mousePosition[1] < 1) {
	   if(curYEndCam < 6371) {
		   curYEndCam += 50;
		   
		   curYCam += 50;
		  
	   }
   }
   else if (mousePosition[1] > float(mainScreenHeight) - 1) {
	   if(curYCam > 49) {
		   
		   curYEndCam -= 50;
		   curYCam -= 50;
	   }
   }
   moveScreen();

}
void QtMainGame::initializeGL()										// All Setup For OpenGL Goes Here
{
	setAcceptDrops(true);

	if (!LoadGLTextures())								// Jump To Texture Loading Routine
	{
		return;									// If Texture Didn't Load Return FALSE
	}
	ctrl = control::getInstance();
	set.createGrid(("Data/map2.txt"));
	collisionGrid* qdTree = new collisionGrid(set.getGrid()->getGrid()->size(),set.getGrid()->getGrid()[0].size());
	ctrl->setColTree(qdTree);
	ctrl->setMainGrid(set.getGrid());
	ctrl->setUpInitial();
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);	// Enable Light One
}

void QtMainGame::paintGL()									// Here's Where We Do All The Drawing
{
	if(this->isActiveWindow()) {
		getMouseInfo();
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	ctrl->go();
	moveScreen();

}



void QtMainGame::mousePressEvent(QMouseEvent *e)
{
	setFocus();
	calculateMouseClickMapPoint(e);
	if(ctrl->getDroneBuilding()) {
		ctrl->setDroneBuilding(false);
		ctrl->addPlayerBuilding(xPoint,yPoint);
	}
	
	if (e->button() == Qt::LeftButton) {
		dragStartPosition = new point2d(xPoint,yPoint);
		dragMousePosition = e->pos();
		calculateMouseClickMapPoint(e);
		ctrl->playerSelect(xPoint,yPoint);
	}
	else if(e->button() == Qt::RightButton) {
		calculateMouseClickMapPoint(e);
		playerControl* player = ctrl->getPlayerControl();
		point2d tar(xPoint/100,yPoint/100);
		player->moveSelected(tar,attackMove);
		vector<sprite*> selected = ctrl->getPlayerSelect();
		//for(int a=0;a<selected.size();a++) {
		//	if(selected[a]->getMovable() == true) {
		//		selected[a]->move(new point2d(xPoint/100,yPoint/100),attackMove);
		//	}
		//	
		//}
	}
	attackMove = false; // reset attack hotkey after mouse event

}
void QtMainGame::mouseMoveEvent(QMouseEvent *e) {
	calculateMouseClickMapPoint(e);
	ctrl->setDroneBuildPos(xPoint,yPoint);
}

void QtMainGame::keyPressEvent(QKeyEvent *e) {
	switch(e->key()) {
	case Qt::Key_A:
		attackMove = true;
	}

}

void QtMainGame::mouseReleaseEvent(QMouseEvent *e) {
	if(e->pos()!=dragMousePosition && e->button() == Qt::LeftButton) {
		dragMouseEndPosition = e->pos();
		calculateMouseClickMapPoint(e);
		dragEndPosition = new point2d(xPoint,yPoint);
		top = new point2d(0,0);
		bottom = new point2d(0,0);
		if(dragStartPosition->getY() < dragEndPosition->getY()) {
			top->setY(dragStartPosition->getY());
			bottom->setY(dragEndPosition->getY());
		}
		else { 
			top->setY(dragEndPosition->getY()); 
			bottom->setY(dragStartPosition->getY()); 
		}

		if(dragStartPosition->getX() < dragEndPosition->getX()) {
			top->setX(dragStartPosition->getX());
			bottom->setX(dragEndPosition->getX());
		}

		else { 
			top->setX(dragEndPosition->getX()); 
			bottom->setX(dragStartPosition->getX());
		}

		ctrl->playerSelect(top,bottom);
	}

}
void QtMainGame::calculateMouseClickMapPoint(QMouseEvent *e) {
	middleXpoint = (adjustedXEndCam-adjustedXCam)*(e->pos().x()/(float)width());
	xPoint = adjustedXCam + middleXpoint;
	middleYpoint = (curYEndCam-curYCam)*(1.0f-(e->pos().y()/(float)height()));
	yPoint = curYCam + middleYpoint;
}

void QtMainGame::timeOutSlot()
{
	timeOut();
}

void QtMainGame::timeOut()
{
	updateGL();
}
void QtMainGame::timerEvent(QTimerEvent *event)
{
  QTime qtime = QTime::currentTime();
  QString stime = qtime.toString(Qt::LocalDate);
  timeOut();
}

void QtMainGame::wheelEvent(QWheelEvent *event){
	//if(event->delta() > 0) {
	//	zoomIn(event->pos().x(),event->pos().y());
	//}
	//else if(event->delta() < 0) {
	//	zoomOut(event->pos().x(),event->pos().y());
	//}
 //   repaint();
}

void QtMainGame::setMainScreenPara(float xPos,float yPos,float width, float height) {
	mainScreenWidth = width;
	mainScreenHeight = height;
	screenX = xPos;
	screenY = yPos;
}