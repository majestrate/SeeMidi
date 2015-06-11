#ifndef MIDIVISUALIZER_H
#define MIDIVISUALIZER_H

#include <QGLWidget>
#include "johnwalkercolormaker.h"
#include "mainwindow.h"

class MidiVisualizer : public QGLWidget
{
    Q_OBJECT
public:
    explicit MidiVisualizer(QWidget *parent = 0);
    void connectToMain();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void clear();
public slots:
    void paintGL(int& message_status, float& param1,
                 float& param2, float& param3,
                 int& widgetIndex);
private:
    int widgetNumber, i;
    //noteGraph
    GLfloat *currPoint;
    GLint *currNoteColor;
    //smv
    float r,g,b;
    JohnWalkerColorMaker jwcm();
};

#endif // MIDIVISUALIZER_H
