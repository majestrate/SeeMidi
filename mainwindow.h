#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QString>
#include <QStackedWidget>
#include "midifeedback.h"


#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

#define NOTE_OFF 128
#define NOTE_ON 144
#define PITCH_BEND 224

#define SIMPLE_TRIANGLE 1
#define EXPANDING_TRIANGLE 2
#define NOTE_GRAPH 3


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void sendMidiData(int& message_status, float& param1,
                      float& param2, float& param3,
                      int& widgetIndex);

private slots:
    void on_pButton_prevWidget_clicked();
    void on_pButton_nextWidget_clicked();
    void driver();
    void on_performanceModeCheckBox_clicked();

private:
    QTimer theTimer;

    MidiFeedback theMF;

    Ui::MainWindow *ui;

    int message_status, i, currentVisualization, nVisualizations;
    long ttime;

    unsigned char second_byte, third_byte;
    unsigned short pitch_bend;

    double tDelta;
    float normalizedIntensity, normalizedNote, noteName, normalizedTime, normalizedBend;
    float normalizedPitchBendBaseline, pitch_bendf;

    bool performanceMode;
};

#endif // MAINWINDOW_H
