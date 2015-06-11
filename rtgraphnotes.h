#ifndef RTGRAPHNOTES_H
#define RTGRAPHNOTES_H

#include <QGLWidget>
#include "mainwindow.h"

class RTGraphNotes : public QGLWidget
{
        Q_OBJECT
public:
    explicit RTGraphNotes(MainWindow *parent = 0);
    void connectToMain();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public slots:
    void paintGL(int& message_status, float& param1,
                 float& param2, float& param3,
                 int& widgetIndex);
private:
    int widgetNumber,i;
    GLfloat *currPoint;
};
#endif // RTGRAPHNOTES_H
