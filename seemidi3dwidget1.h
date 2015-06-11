#ifndef SEEMIDI3DWIDGET1_H
#define SEEMIDI3DWIDGET1_H

#include <QGLWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "midifeedback.h"

class SeeMIDI3dWidget1 : public QGLWidget
{
    Q_OBJECT
public:
    explicit SeeMIDI3dWidget1(QWidget *parent = 0);

    void start();
    void stop();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    MidiFeedback mf;
private:
    QElapsedTimer functionTimer;
    long long int averageTime;
    int midiData[4];
    int status_byte, note_byte, intensity_byte, ttime;
    float normalizedIntensity, normalizedNote, noteName, normalizedTime;
    QTimer theTimer;
};

#endif // SEEMIDI3DWIDGET1_H
