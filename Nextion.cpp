#if defined(ARDUINO) && ARDUINO >= 100  // Arduino IDE Version
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Nextion.h"


// Macro for the selection of the Serial Port

#define sendData(args)  (Serial5.write(args))    // Write Over Serial
#define availableData() (Serial5.available())    // Check Serial Data Available
#define readData()      (Serial5.read())         // Read Serial Data
#define peekData()      (Serial5.peek())         // Peek Serial Data
#define beginCom(args)  (Serial5.begin(args))    // Begin Serial Comunication
#define endCom()        (Serial5.end())          // End Serial Comunication
// Macro for Timing

void Nextion::begin(long baud)
{
	beginCom(baud);
}

void Nextion::print(const char[])
{
	Serial5.print("m1.txt=\"eingabe\"");
}
