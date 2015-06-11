#include "testsmv.h"

TestSMV::TestSMV(MainWindow *parent) :
    QGLWidget(parent)
{
    //std::cout<< (this->parent()==NULL) <<std::endl;
}

void TestSMV::connectToMain(){
    widgetNumber = 1;//currently hard coded

    std::cout<< "I am " << widgetNumber <<std::endl;
    connect(((MainWindow*)this->window()),
            SIGNAL(sendMidiData(int&,float&,float&,float&,int&)),
            this,
            SLOT(paintGL(int&,float&,float&,float&,int&)));
}

void TestSMV::initializeGL(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestSMV::paintGL(){
}

void TestSMV::paintGL(int &message_status, float &param1,
                      float &param2, float &param3, int &widgetIndex){

    if(widgetIndex == widgetNumber){//only redraw if this widget is selected and on note played
        switch(message_status){

        case NOTE_OFF:
            break;
        case NOTE_ON:
            r = param1;
            g = param2;
            b = param3;
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_TRIANGLES);
            glColor3f(r,0,0);
            glVertex3f(-0.5, -0.5, 0);
            glColor3f(0,g,0);
            glVertex3f( 0.5, -0.5, 0);
            glColor3f(0,0,b);
            glVertex3f( 0.0, 0.5, 0);
            glEnd();
            break;
        case PITCH_BEND:
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_TRIANGLES);
            glColor3f(r,0,0);
            glVertex3f(-param1, -param1, 0);
            glColor3f(0,g,0);
            glVertex3f( param1, -param1, 0);
            glColor3f(0,0,b);
            glVertex3f( 0.0, param1, 0);
            glEnd();
            break;
        }
    }
    this->update();
}

void TestSMV::resizeGL(int w, int h){
}
