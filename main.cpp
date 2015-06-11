/*  by Charles Singleton(+)
 *
 *  (+)Incorporates snippets from rtmidi tutorials http://www.music.mcgill.ca/~gary/rtmidi/
 *  I relied on the tutorials and provided tests (in rtmidiTests) to understand rtmidi
 *  and copied/expanded "trivial" snippets. --> most helpful/utilized code from "qmidiin.cpp"
 *
 *  other sources include various web sources...
 *  this video was really helpful: https://www.youtube.com/watch?v=1nzHSkY4K18
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
