/*
 * MidiIn Wrapper
 * MidiIn setup is done here
 *
 */

#include <QString>
#include "midifeedback.h"
#include <signal.h>

bool done;
static void finish( int /*ignore*/ ){ done = true; }

MidiFeedback::MidiFeedback()
{
    port = 0;   
    setupMidiIn(); //setup the midiin Object
    // Install an interrupt handler function.
    //this is needed otherwise it crashes on close
    (void) signal(SIGINT, finish);
}

MidiFeedback::~MidiFeedback(){
    delete midiin;
}

//update vars by reference
void MidiFeedback::getMidiData(int &message_status, unsigned char &second_byte,
                               unsigned char &third_byte, double &tstamp){
    stamp = midiin->getMessage( &message );
    nBytes = message.size();


    //if there is no message, accessing &message will explode
    if(message.size()>0){
        //hard coded only sysex messages, so we know there are 3 bytes
        message_status = message[0];
        second_byte = message[1];
        third_byte = message[2];
        tstamp = stamp;
        /*
        std::cout<< status_byte << ", "
                 << note_byte << ", "
                 << intensity_byte << ", "
                 << ttime << ", "
                 << notePlayed << std::endl;
                 */
   }
}

void MidiFeedback::setupMidiIn(){
    // RtMidiIn constructor
    try {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError &error) {
        // Handle the exception here
        error.printMessage();
    }


    // Check inputs. Exit if no ports
    unsigned int nPorts = midiin->getPortCount();
    if(nPorts < 1){
        std::cout << "no ports detected!!\n";
        exit( EXIT_FAILURE );
    }

    //on my setup (unix based) I expect to find the MIDI input at port 0
    try {
        midiin->openPort( port );
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        delete midiin;
    }

    // accept sysex, ignore timing and active sensing messages.
    // thus we can hard code parts of MIDIupdate
    midiin->ignoreTypes( false, true, true );
}
