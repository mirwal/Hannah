#if defined(ARDUINO) && ARDUINO >= 100  // Arduino IDE Version
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Tasten.h"

// Macro for the selection of the Serial Port

#define sendData(args)  (Serial4.write(args))    // Write Over Serial
#define availableData() (Serial4.available())    // Check Serial Data Available
#define readData()      (Serial4.read())         // Read Serial Data
#define peekData()      (Serial4.peek())         // Peek Serial Data
#define beginCom(args)  (Serial4.begin(args))    // Begin Serial Comunication
#define endCom()        (Serial4.end())          // End Serial Comunication
// Macro for Timing

#define delayus(args) (delayMicroseconds(args))  // Delay Microseconds


Tasten::Tasten()
{
}


Tasten::~Tasten()
{
}
void Tasten::begin(long baud)
{
	beginCom(baud);
}

void Tasten::lesen()
{
	offline_Counter++;
		
	int Time_Counter = 0;
	while ((availableData() < 22) & (Time_Counter < 40)) {
		Time_Counter++;
		delayus(1000);
	}

	while (availableData() > 0) {
		offline_Counter = 0;
		Incoming_Byte = readData();
		if ((Incoming_Byte == 0x0A) & (readData() == 0x7E)) {
			int count = 0;
			uint8_t  speicher[12];
			do {// Hebel und Poti und Feader lesen
				MSB = readData(); delayus(1000);
				LSB = readData(); delayus(1000);
				speicher[count] = decodiren(MSB, LSB);
				if (speicher[count++] > 128)
					count = 9;
			} while ((readData() == 0xFF)&(count <= 7));

			Incoming_Byte = readData();
			if (Incoming_Byte < 128)speicher[count++] = Incoming_Byte;

			if (count == 8) {
				//Incoming_Byte = speicher[7];
			
				int i = 0;
				for(i = 0 ; i < count; i++) {setTasteWert(i, speicher[i]);}
				// Taster lesen
				for (int j = 7; j > 0; j--) {
					if (((Incoming_Byte >> 6) % 2) == 0) {setTasteStatus(14 - j, false);}
					else {setTasteStatus(14 - j, true);	}
					Incoming_Byte <<= 1;
				}

			}
			Incoming_Byte = readData();
			if (Incoming_Byte < 255){
				speicher[count++] = Incoming_Byte;
			}
			
			// Taster T1 bis T8 lesen
			if (count == 9) {
				for (int t = 7; t > 0; t--) {
					if (((Incoming_Byte >> 7) % 2) != 0) {
						setTasteStatus(29 - t, true);
					}
					else {
						setTasteStatus(29 - t, false);
					}
					Incoming_Byte <<= 1;
				}
			}
			count = 0;
			/**/
		}
	}

}
bool Tasten::ist_offline()
{
	if (offline_Counter > 30)return true;
	return false;
}
bool Tasten::setTasteWert(unsigned char ID, uint8_t wert)
{
	if (wert > 128)	return false;
	TasteWert[ID] = wert;
	PotiWert[ID] = wert;
	return true;
}
uint8_t Tasten::getTasteWert(unsigned char ID)
{
	if (TasteWert[ID] < 255) 
		return TasteWert[ID];
	return TasteWert[ID];
}
int Tasten::getTasteWert(unsigned char ID, bool t)
{
	if (PotiWert[ID] < 255)
		return PotiWert[ID];
	return PotiWert[ID];
}

bool Tasten::getTasteStatus(unsigned char ID)
{
	if (TasteStatus[ID]) return true;
	return false;
}
bool Tasten::sendBefehl(unsigned char befehl)
{
	if (ist_befehl == befehl)	return false;

	switch (befehl)
	{
	case (Akku):
		sendData(StartBit);
		delayus(1000);
		sendData(Akku);	// "Akkuobjekt... "
		delayus(1000);
		ist_befehl = Akku;
		break;
	case (Online):
		sendData(StartBit);
		delayus(1000);
		sendData(Online);	// "Akkuobjekt... "
		delayus(1000);
		ist_befehl = Online;
		break;

	default:
		ist_befehl = 0x0;
		break;
	}
	return true;
}
bool Tasten::setTasteStatus(unsigned char ID, bool Status)
{
	if ((TasteStatus[ID]) == (Status)) return false;

	if (Status==true) { (TasteStatus[ID]) = true; }
	else {(TasteStatus[ID]) = false;}
	return true;
}


Tasten Tast;

//1011000