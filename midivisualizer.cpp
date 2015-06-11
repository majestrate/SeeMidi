#include "midivisualizer.h"

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

GLint noteColors[12][3];
GLfloat brightColors[255][3];

//GLdouble pitchBendRange[381][3];
//16383 and divisors:   1       3       43      127
//                      16383   5461    381     129

MidiVisualizer::MidiVisualizer(QWidget *parent) :
    QGLWidget(parent)
{
    int i;
    QColor tmp;
    currPoint = new GLfloat[3];
    currNoteColor = new GLint[3];
    //double tr,tg,tb;

    for(i=0;i<12;i++){
        //noteColors[i].setHsv(i*(255/12),255,255);
        tmp.setHsv((i*255)/12,255,255);
        noteColors[i][0]=tmp.red();
        noteColors[i][1]=tmp.green();
        noteColors[i][2]=tmp.blue();
    }

    for(i=0;i<255;i++){
        //brightColors[i].setHsv(i,255,255);
        tmp.setHsv(i,255,255);
        brightColors[i][0]=tmp.red()/255.0f;
        brightColors[i][1]=tmp.green()/255.0f;
        brightColors[i][2]=tmp.blue()/255.0f;
    }


    /*generate note colors
    for(i=0;i<12;i++){
        tmp = (i+1) * (10000/12);
        JohnWalkerColorMaker(tmp, tr, tg, tb);
        //std::cout << tr << ", " << tg << ", " << tb <<std::endl;
        noteColors[i][0] = tr;
        noteColors[i][1] = tg;
        noteColors[i][2] = tb;
    }

    //generate pitch bend range colors
    /*
    for(i=0;i<381;i++){
        tmp = (i+1) * (10000/381);
        JohnWalkerColorMaker(tmp, tr, tg, tb);
        //std::cout << tr << ", " << tg << ", " << tb <<std::endl;
        noteColors[i][0] = tr;
        noteColors[i][1] = tg;
        noteColors[i][2] = tb;
    }
    */
}

void MidiVisualizer::connectToMain(){
    widgetNumber = 0;//currently hard coded

    std::cout<< "I am " << widgetNumber <<std::endl;
    connect(((MainWindow*)this->window()),
            SIGNAL(sendMidiData(int&,float&,float&,float&,int&)),
            this,
            SLOT(paintGL(int&,float&,float&,float&,int&)));
}

void MidiVisualizer::initializeGL(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    this->update();
}

void MidiVisualizer::clear(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    this->update();
}

void MidiVisualizer::paintGL(){
}

void MidiVisualizer::paintGL(int &message_status, float &param1,
                             float &param2, float &param3, int& widgetIndex){

    switch(widgetIndex){
    case SIMPLE_TRIANGLE:
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
        break;
    case EXPANDING_TRIANGLE:
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
            glVertex3f(-param2, -param2, 0);
            glColor3f(0,g,0);
            glVertex3f( param2, -param2, 0);
            glColor3f(0,0,b);
            glVertex3f( 0.0, param2, 0);
            glEnd();
            break;
        }break;
    case NOTE_GRAPH:
        switch(message_status){
        case NOTE_OFF:
            break;
        case NOTE_ON:
            currPoint = notePoints[(int)param1];
            currNoteColor = noteColors[(int)param1];

            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(param2*100.0);
            glBegin(GL_POINTS);

            glColor3ub(currNoteColor[0],
                    currNoteColor[1],
                    currNoteColor[2]);
            glVertex2fv(currPoint);
            glEnd();
            break;
        case PITCH_BEND:
            glClearColor(brightColors[(int)param3][0],
                    brightColors[(int)param3][1],
                    brightColors[(int)param3][2],0);
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(param1*100.0);
            glBegin(GL_POINTS);
            glColor3ub(currNoteColor[0],
                    currNoteColor[1],
                    currNoteColor[2]);
            glVertex2fv(currPoint);
            glEnd();

            break;
        }break;
    default:
        switch(message_status){
        case NOTE_OFF:
            break;
        case NOTE_ON:
            break;
        case PITCH_BEND:
            break;
        }break;
    }
    this->update();
}

void MidiVisualizer::resizeGL(int w, int h){
}

/*
 *
 * void TestSMV::paintGL(int &message_status, float &param1,
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

 * void RTGraphNotes::paintGL(int &message_status, float &param1,
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
            /
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(param1*100.0);
            glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2fv(currPoint);
            glEnd();
            /

            break;
        }
    this->update();
    }
}
 */
