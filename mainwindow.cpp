#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString noteArray[12]= {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
const QString visualizerNames[]={"basicTriangle","expandingTriangle","noteSquares"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //init vars
    nVisualizations = 3;
    currentVisualization = 1;

    message_status = 128; //note off
    second_byte = third_byte = 0;
    tDelta= 0;
    ttime = 0;
    i=0;

    performanceMode = false;

    normalizedPitchBendBaseline = (float)0x2000/0x3FFF;

    //ui init
    ui->setupUi(this);
    ui->widget_select_label->setText(visualizerNames[currentVisualization-1]);


    //connect visualizer widget
    ui->midiVisualizer->connectToMain();

    //clear the visualizer

    //kickoff the driver
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(driver()));
    theTimer.start(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::driver(){//drive the program here
    ttime=(ttime+1)%255;

    if(!performanceMode){
        ui->time_holder->setText(QString::number(ttime));              //tDelta
    }
    //update base midi vars
    theMF.getMidiData(message_status, second_byte, third_byte, tDelta);
    //std::cout << theStackedWidgetCurrIndex << std::endl;
    /*
    if(status_byte!=128){
        std::cout << "s: " << status_byte
                  << " n: " << second_byte
                  << " i: " << third_byte
                  << " t: " << tDelta
                  << " np: " << noteArray[second_byte%12].toStdString()
                  << std::endl;
    }
    */

    switch(message_status){
    case NOTE_OFF://note off
        break;
    case NOTE_ON:
        //note on
        //status, note_byte, intensity_byte
        //update statusBar if not focused on performance
        if(!performanceMode){
            ui->note_played_holder->setText(noteArray[second_byte%12]);     //note played
            ui->intensity_holder->setText(QString::number(third_byte));    //intensity
        }
        //do calculations
        normalizedNote = second_byte%12;
        normalizedIntensity = third_byte/127.0; //assuming max intensity is 127
        normalizedTime = (float)ttime;
        //update current widget

        emit sendMidiData(message_status,
                          normalizedNote,
                          normalizedIntensity,
                          normalizedTime,
                          currentVisualization);
        break;
    case PITCH_BEND://pitch bend
        pitch_bend = (unsigned short)third_byte;
        pitch_bend <<= 7;
        pitch_bend |= (unsigned short)second_byte;

        normalizedIntensity = third_byte/127.0; //assuming max intensity is 127
        normalizedBend = (float)pitch_bend/(float)0x3FFF;
        pitch_bendf = 255.0 * normalizedBend;

        //std::cout << pitch_bend << ", " << pitch_bendf <<std::endl;

        if(!performanceMode){
            ui->pbend_holder->setText(QString::number(pitch_bend));//normalizedBend-normalizedPitchBendBaseline));
        }
        emit sendMidiData(message_status,
                          normalizedIntensity,
                          normalizedBend,
                          pitch_bendf,
                          currentVisualization);
        break;
    }
}

void MainWindow::on_pButton_prevWidget_clicked()
{
    if(currentVisualization>1){
        currentVisualization--;
        ui->midiVisualizer->clear();
        ui->widget_select_label->setText(visualizerNames[currentVisualization-1]);
    }
}

void MainWindow::on_pButton_nextWidget_clicked()
{
    if(currentVisualization<nVisualizations){
        currentVisualization++;
        ui->midiVisualizer->clear();
        ui->widget_select_label->setText(visualizerNames[currentVisualization-1]);
    }
}

void MainWindow::on_performanceModeCheckBox_clicked()
{
    performanceMode = !performanceMode;
}
