#include "glwidget.h"

GLWidget::GLWidget(MainWindow *parent) :
    QGLWidget(parent)
{
    //std::cout<< (this->parent()==NULL) <<std::endl;
}

void GLWidget::connectToMain(){
    widgetNumber = 0;//currently hard coded

    std::cout<< "I am " << widgetNumber <<std::endl;
    connect(((MainWindow*)this->window()),
            SIGNAL(sendMidiData(int&,float&,float&,float&,int&)),
            this,
            SLOT(paintGL(int&,float&,float&,float&,int&)));
}

void GLWidget::initializeGL(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLWidget::paintGL(){
}

void GLWidget::paintGL(int &message_status, float &param1,
                       float &param2, float &param3, int& widgetIndex){

    //std::cout << widgetNumber << std::endl;
    if(widgetIndex == widgetNumber){//only redraw if this widget is selected
        switch(message_status){
        case NOTE_OFF:
            break;
        case NOTE_ON:
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_TRIANGLES);
            glColor3f(param1/12.0,0,0);
            glVertex3f(-0.5, -0.5, 0);
            glColor3f(0,param2,0);
            glVertex3f( 0.5, -0.5, 0);
            glColor3f(0,0,param3);
            glVertex3f( 0.0, 0.5, 0);
            glEnd();
            break;
        case PITCH_BEND:
            break;
        }
    this->update();
    }
}

void GLWidget::resizeGL(int w, int h){
}
