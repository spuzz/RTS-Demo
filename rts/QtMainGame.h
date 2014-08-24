#ifndef QTMAINGAME_H
#define QTMAINGAME_H

#include "QtMain.h"
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "texLoad.h"
#include "grid.h"
#include "setup.h"
#include <png.h>
#include "control.h"
#include <QGLWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>

namespace Ui {
    class Form;
} // namespace Ui



class QtMainGame : public QGLWidget {
	Q_OBJECT
public:
	explicit QtMainGame(QWidget *parent = 0);
	void initializeGL();
	int LoadGLTextures();	
	GLvoid moveScreen();
	GLvoid resizeGL(GLsizei width, GLsizei height);
	GLvoid zoomIn(float x, float y);
	GLvoid zoomOut(float x, float y);
	void getMouseInfo();
	void paintGL();
	
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

	void setMainScreenPara(float xPos,float yPos,float width, float height);
	void timeOut();
	void calculateMouseClickMapPoint(QMouseEvent *e);


	

protected slots:
	void timeOutSlot();
	void timerEvent(QTimerEvent *event);
	
signals:
	void timeout();

private:
	Ui::Form *ui;
	bool	keys[258];			// Array Used For The Keyboard Routine
	bool	active;		// Window Active Flag Set To TRUE By Default
	bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
	bool	light;				// Lighting ON/OFF ( NEW )
	bool	lp;					// L Pressed? ( NEW )
	bool	fp;					// F Pressed? ( NEW )
	bool	attackMove;			// A Pressed?

	vector<float> mousePosition;
	float middleXpoint,middleYpoint;
	float xPoint,yPoint;
	float curXCam;
	float curYCam;
	float curXEndCam;
	float curYEndCam;
	float adjustedXCam;
	float adjustedXEndCam;
	float mouseWheel;
	float zoomspeed;
	float widthToHeight;
	float mainScreenWidth;
	float mainScreenHeight;
	float screenX;
	float screenY;

	GLfloat	xrot;				// X Rotation
	GLfloat	yrot;				// Y Rotation
	GLfloat xspeed;				// X Rotation Speed
	GLfloat yspeed;				// Y Rotation Speed
	GLfloat	z;			// Depth Into The Screen

	GLfloat  LightAmbient[4];
	GLfloat  LightDiffuse[4];
	GLfloat  LightPosition[4];

	GLuint	filter;				// Which Filter To Use
	GLuint	texture[3];			// Storage For 3 Textures
	float ZOOM;
	setup set;
	control* ctrl;
	QTimer *m_timer;
	int timerInterval;
	QPoint dragMousePosition,dragMouseEndPosition;
	point2d* dragStartPosition;
	point2d* dragEndPosition;
	point2d* top;
	point2d* bottom;
};

#endif // QTMAINGAME_H