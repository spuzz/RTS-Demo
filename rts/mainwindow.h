#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include "QtMainGame.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();
	void keyPressEvent(QKeyEvent *event);
	void updateGeom();
	void resizeEvent(QResizeEvent *event);
private:
	int heightForWidth ( int w );
	QtMainGame *glWidget;
};

#endif // MAINWINDOW_H
