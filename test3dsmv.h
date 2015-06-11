#ifndef TEST3DSMV_H
#define TEST3DSMV_H

#include <QGLWidget>
#include <QtOpenGL>
#include "mainwindow.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

class Test3dSMV : public QGLWidget
{
    Q_OBJECT
public:
    explicit Test3dSMV(MainWindow *parent = 0);
    void connectToMain();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public slots:
    virtual void paintGL(int& status_byte, float& param1,
                 float& param2, float& param3,
                 int& widgetIndex);
private:
    int widgetNumber;
};

#endif // TEST3DSMV_H
