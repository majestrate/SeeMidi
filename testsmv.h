#ifndef TESTSMV_H
#define TESTSMV_H

#include <QGLWidget>
#include "mainwindow.h"

class TestSMV : public QGLWidget
{
    Q_OBJECT
public:
    explicit TestSMV(MainWindow *parent = 0);
    void connectToMain();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public slots:
    void paintGL(int &message_status, float& param1,
                 float& param2, float& param3,
                 int& widgetIndex);
private:
    int widgetNumber;
    float r,g,b;
};

#endif // TESTSMV_H
