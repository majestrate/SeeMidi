//most of code sourced from: https://wiki.qt.io/Introduction-to-Qt3D
//then edited

#include "test3dsmv.h"

GLfloat normals[]={ -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
          0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f };

Test3dSMV::Test3dSMV(MainWindow *parent) :
    QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::Rgba | QGL::DoubleBuffer | QGL::DepthBuffer));


}

void Test3dSMV::connectToMain(){
    widgetNumber = 1;//currently hard coded

    std::cout<< "I am " << widgetNumber <<std::endl;
    connect(((MainWindow*)this->window()),
            SIGNAL(sendMidiData(int&,float&,float&,float&,int&)),
            this,
            SLOT(paintGL(int&,float&,float&,float&,int&)));
}

void Test3dSMV::initializeGL(){
    float ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
    float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    float specularity[] = { 1.0, 1.0, 1.0, 1.0 };
    float shininess[] = { 60.0 };
    float lightPosition[] = { 0.0, 50.0, 50.0, 1.0 };

   // Enable lighting with one light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

   // Properties of the objects' materials
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularity); // Reflectance
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

   // Enable ambient light usage
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

   // Position of the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void Test3dSMV::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Vertices
    static const float vertices[6][4][3] = {
        { { 1.0, -1.0, 1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0 } },
        { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { -1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 } },
        { { 1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, 1.0, -1.0 } },
        { { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } },
        { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } },
        { { -1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 } }
    };

    for (int i = 0; i < 6; ++i) {
        glBegin(GL_QUADS);
        glNormal3fv(normals[i]);
        for (int j = 0; j < 4;++j)
            glVertex3fv(vertices[i][j]);
        glEnd();
    }
}

void Test3dSMV::paintGL(int& status_byte, float &param1,
                        float &param2, float &param3, int& widgetIndex){
    /*
    //std::cout << widgetNumber << std::endl;
    if(widgetIndex == widgetNumber && status_byte == 144){//only redraw if this widget is selected and on note played, ignore note-off signals

    }
    this->update();
    */
}

void Test3dSMV::resizeGL(int w, int h){

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Defines the perspective projection
    glLoadIdentity();
    gluPerspective(45, aspectRatio, 1, 500);

    // Defines the position of the camera and the target
    glLoadIdentity();
    gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
}


