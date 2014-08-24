#pragma once

#include <qgl.h>


class QtMain : public QGLWidget
{
public:
  QtMain( int timerInterval=0, QWidget *parent=0, char *name=0 );

protected:
  virtual void initializeGL() = 0;
  virtual void resizeGL( int width, int height ) = 0;
  virtual void paintGL() = 0;
  
  virtual void keyPressEvent( QKeyEvent *e );
  
  virtual void timeOut();
};