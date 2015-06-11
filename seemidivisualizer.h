#ifndef SEEMIDIVISUALIZER_H
#define SEEMIDIVISUALIZER_H

#include <QGLWidget>
#include "mainwindow.h"

class SeeMIDIVisualizer : public QGLWidget
{
    Q_OBJECT
public:
    explicit SeeMIDIVisualizer(MainWindow *parent = 0);
public slots:
    virtual void paintGL(int& status_byte, float& param1,
                 float& param2, float& param3,
                 int& widgetIndex) = 0;
protected:
    int widgetNumber;
    virtual void connectToMain() = 0;
    virtual void initializeGL() = 0;
    virtual void paintGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
};

#endif // SEEMIDIVISUALIZER_H
