#ifndef MIDIFEEDBACK_H
#define MIDIFEEDBACK_H
#include "RtMidi.h"

class MidiFeedback
{
public:
    MidiFeedback();
    ~MidiFeedback();
    void getMidiData(int &message_status, unsigned char& second_byte,
                     unsigned char& third_byte, double& tstamp);

private:
    void setupMidiIn();
    //MIDI vars. Some are in mainwindow.cpp
    RtMidiIn *midiin;
    unsigned int port; //target MIDI port

    std::vector<unsigned char> message;     //vector for queing midi messages
    int nBytes;             //used to hold message size
    double stamp;    //handle total time tracking
    //end MIDI vars
};

#endif // MIDIFEEDBACK_H
