#pragma once
#define HL_UD				0
#define HL_LR 				1
#define HR_UD				2
#define HR_LR				3
#define Poti				4
#define Fader				5
#define Flap				6
#define HR1					7
#define HR2					8
#define HR3					9
#define HL1					10
#define HL2					11
#define HL3					12
#define TRAINER				13

#define T1					21
#define T2					22
#define T3					23
#define T4					24
#define T5					25
#define T6					26
#define T7					27
#define T8					28

class Tasten
{
public:

	Tasten();
	~Tasten();
	void begin(long baud);
	void lesen();
	bool ist_offline();
	int offline_Counter = 100;
	uint8_t getTasteWert(unsigned char ID);
	int getTasteWert(unsigned char ID,bool t);
	bool getTasteStatus(unsigned char ID);
	bool sendBefehl(unsigned char befehl);
	enum Befehl
	{
		ERROR		=	(0xFF),
		StartBit	=	(0xF1),
		Online		=	(0x90),
		Akku,				// "Akkuobjekt... "
		mirwal,
		TESTEN,
			
	}; 
private:
	unsigned char ist_befehl = 0x00;
	unsigned char Incoming_Byte;
	bool TasteStatus[18] = { false };
	uint8_t TasteWert[8];					//unsigned char	1 byte	0 to 255
	int PotiWert[8];					//unsigned char	1 byte	0 to 255

	uint8_t MSB = 0;									// HIGH Bit und LOW Bit ... zwei daten auslesen
	uint8_t LSB = 0;
	bool setTasteWert(unsigned char ID, uint8_t wert);
	uint8_t decodiren(uint8_t MSB, uint8_t LSB)
	{
	//	return (LSB + (MSB * 256) + MSB);
		return (MSB << 8) + LSB;
	}
	bool setTasteStatus(unsigned char ID, bool Status);


};

extern Tasten Tast;