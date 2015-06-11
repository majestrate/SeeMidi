#include "rtgraphnotes.h"

GLfloat notePoints[12][2] = {
    {-0.75f,0.75f},
    {-0.25f,0.75f},
    {0.25f,0.75f},
    {0.75f,0.75f},
    {0.75f,0.25f},
    {0.75f,-0.25f},
    {0.75f,-0.75f},
    {0.25f,-0.75f},
    {-0.25f,-0.75f},
    {-0.75f,-0.75f},
    {-0.75f,-0.25f},
    {-0.75f,0.25f}};



RTGraphNotes::RTGraphNotes(MainWindow *parent) :
    QGLWidget(parent)
{
    //std::cout<< (this->parent()==NULL) <<std::endl;
}

void RTGraphNotes::connectToMain(){
    widgetNumber = 2;//currently hard coded

    std::cout<< "I am " << widgetNumber <<std::endl;
    connect(((MainWindow*)this->window()),
            SIGNAL(sendMidiData(int&,float&,float&,float&,int&)),
            this,
            SLOT(paintGL(int&,float&,float&,float&,int&)));
}

void RTGraphNotes::initializeGL(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RTGraphNotes::paintGL(){
}

void RTGraphNotes::paintGL(int &message_status, float &param1,
                       float &param2, float &param3, int& widgetIndex){


    if(widgetIndex == widgetNumber){//only redraw if this widget is selected
        switch(message_status){
        case NOTE_OFF:
            break;
        case NOTE_ON:
            currPoint = notePoints[(int)param1];

            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(param2*100.0);
            glBegin(GL_POINTS);

            glColor3f(1,1,1);
            glVertex2fv(currPoint);

            glEnd();
            break;
        case PITCH_BEND:
            /*
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(param1*100.0);
            glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2fv(currPoint);
            glEnd();
            */

            break;
        }
    this->update();
    }
}

void RTGraphNotes::resizeGL(int w, int h){
}
