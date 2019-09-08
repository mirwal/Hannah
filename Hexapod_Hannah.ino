// Jetzt mit Github und getestet

#include <SPI.h>
#include <DynamixelSerial1.h>
#include "Tasten.h"
#include "Hannah.h"
#include "ik.h"
#include "UserFeedback.h"


int Temperature, Voltage, Position;
uint32_t timer_1 = millis();

/*
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
*/


void GrundPosition();
void TastenInterpretieren();
void AufgabeUmsetzen(Hannah);
bool timo_1(uint32_t intervalWert);

bool HR1_flag = false;
bool HR2_flag = false;
bool HR3_flag = false;
bool HL1_flag = false;
bool HL2_flag = false;
bool HL3_flag = false;
bool TrainerFlag = false;


bool T_flag[30] = { false };

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.begin(9600);              // Begin Serial Comunication
	Dynamixel.begin(1000000u, 2);  // Inicialize the servo at 1Mbps and Pin Control 2
	userFeedback.start();
	delay(1500);
	Tast.begin(9600);
	delay(500);


	/*	int IDS = 11;
		for (int i = 0; i < 20; i++) {
			Dynamixel.reset(i);
			delay(1000);
			Dynamixel.setID(i, IDS);
			delay(1000);
			Serial.print(i);
		}
		digitalWrite(LED_BUILTIN, LOW);
		while (true){Serial.println(Dynamixel.readPosition(IDS));	};
	*/

	Serial.println("on");

	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////															///////////
	///////////

	IK.setPosX(0.0f);
	IK.setPosY(0.0f);
	IK.setPosZ(0.0f);
	IK.setRotX(0.0f);
	IK.setRotY(0.0f);
	IK.setRotZ(0.0f);

	IK.LegLiftHeight = 25.0f;
	IK.TravelLengthX = 0.0f;
	IK.TravelLengthZ = 0.0f;
	IK.TravelRotationY = 0.0f;


	
	// OK//
	// IK.getGaitPosX(i)
	// IK.getGaitPosY(i)
	// IK.getGaitPosZ(i)
	// IK.getGaitRotY(i)
	// IK.getGaitRotY(i)
	// IK.FeetPosX_WRT_COXA[i]
	// IK.FeetPosY_WRT_COXA[i]
	// IK.FeetPosZ_WRT_COXA[i]
	// IK.getTotalX(i)			
	// IK.getTotalZ(i)	
	// IK.getTotalY(i)	
	// IK.getStepLegNr(i)
	// IK.getStepLegNrAdd1(i)
	// IK.getStepLegNrRem5(i)
	// IK.getBodyIkX(i)
	// IK.getBodyIkY(i)
	// IK.getBodyIkZ(i)
	// IK.getNewPosX(i)
	// IK.getNewPosY(i)
	// IK.getNewPosZ(i)
	// IK.getIKCoxaAngle(i)
	// IK.getTAngle(i)
	// IK.getIKA1(i)
	// IK.getIKA2(i)
	// IK.getTranformX(i)
	// IK.getTranformY(i)
	// IK.getTranformZ(i)

	///////////
	///////////			///////////
	userFeedback.print_in_Zeile_2("23456789");
	userFeedback.print_in_Zeile_3("erung aus 789");// display a line of text
	
	
	//Warten bis Funke online ist :-)
	do
	{
		Tast.lesen();
	} while (Tast.ist_offline());

	Serial.println("line");

	digitalWrite(LED_BUILTIN, LOW);
}
int serialcounter;
unsigned int CH[20] = { 0 };						// Array für die werte die von der Funke gekommen sind 

uint8_t MSB = 0;									// HIGH Bit und LOW Bit ... zwei daten auslesen
uint8_t LSB = 0;

char inputBuffer[8];								// Char Buffer array für die Digitalen Eingange die von der Funke ausgelesen wurden kurz zwischenTempen
uint8_t BeinOnlineFlag = 0;


//###################################################################
//###################################################################
//###################################################################
//###################################################################
//###################################################################
void loop()
{


	//	digitalWrite(LED_BUILTIN, LOW);

	TastenInterpretieren();
	AufgabeUmsetzen(H);
	// test
	if(!(Tast.getTasteStatus(HR2))){

		userFeedback.print_in_Zeile_1(IK.getIKCoxaAngle(0));
		userFeedback.print_in_Zeile_2(IK.getFemur(0));
		userFeedback.print_in_Zeile_3(IK.getTibia(0));
		userFeedback.print_in_Zeile_4(IK.getPosY());
		

#define CA		160

		IK.setRotY((map(uint8_t(Tast.getTasteWert(HR_LR)), 30, 100, -20, +20)));
		
		IK.setPosY((map(uint8_t(Tast.getTasteWert(HR_UD)), 30, 100, -20, +20)));
		
		
		if (Tast.getTasteStatus(HR1)) {
			int potispeed = map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512);
			for (int i = 0; i < 6; i++) {
				Dynamixel.moveSpeed(1 + i, map(IK.getCoxa(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);

				Dynamixel.moveSpeed(7 + i, map(IK.getFemur(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);
				Dynamixel.moveSpeed(13 + i, map(IK.getTibia(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);
			}
		}
		else {
			Dynamixel.moveSpeed(1, map(IK.getCoxa(0), -45, +45, 512 - CA, 512 + CA), 100);
			Dynamixel.moveSpeed(7, map(IK.getFemur(0), -45, +45, 512 - CA, 512 + CA), 100);
			Dynamixel.moveSpeed(13, map(IK.getTibia(0), -45, +45, 512 - CA, 512 + CA), 100);

		}
		
	}
	if (Tast.getTasteStatus(HR2)) {

		int potispeed = map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512);
		for (int i = 0; i < 6; i++) {
			Dynamixel.moveSpeed(1 + i, map(IK.getCoxa(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);
			Dynamixel.moveSpeed(7 + i, map(IK.getFemur(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);
			Dynamixel.moveSpeed(13 + i, map(IK.getTibia(0 + i), -45, +45, 512 - CA, 512 + CA), potispeed);
		}
		IK.TravelLengthZ = (map(uint8_t(Tast.getTasteWert(HR_UD)), 30, 100, -60, +60));
		IK.TravelLengthX= (map(uint8_t(Tast.getTasteWert(HR_LR)), 30, 100, -60, +60));

		IK.setRotX((map(uint8_t(Tast.getTasteWert(HL_UD)), 30.0, 100.0, -10.0, +10.0)));
		IK.setRotZ((map(uint8_t(Tast.getTasteWert(HL_LR)), 30.0, 100.0, -10.0, +10.0)));

		if (IK.TravelLengthZ < -0 || IK.TravelLengthZ>0 || IK.TravelLengthX < -0 || IK.TravelLengthX>0){
			if (timo_1(500)) {
				long tempUD = (map(uint8_t(Tast.getTasteWert(HR_UD)), 30, 100, -40, +40));
				tempUD = (tempUD < 0) ? (tempUD*-1) : (tempUD);
				long tempLR = (map(uint8_t(Tast.getTasteWert(HR_LR)), 30, 100, -40, +40));
				tempLR = (tempLR < 0) ? (tempLR*-1) : (tempLR);

				long temp = ((tempUD + tempLR) >= 60) ? (60) : (tempUD + tempLR);
				IK.LegLiftHeight = (temp < 0) ? (temp*-1) : (temp);
				IK.AddGaitStep();
			}
		}else {
			IK.LegLiftHeight = 0.0f;
		}
		
		IK.setPosZ(map(uint8_t(Tast.getTasteWert(Fader, true)), 0, 128, -20, +20));

	}


	//delay(300);

}


//###################################################################
//###################################################################
//###################################################################
//###################################################################
//###################################################################



void GrundPosition()
{

	for (int i = 7; i <= 12; ++i) {
		Tast.lesen();
		if (i % 2 == 0) Dynamixel.moveSpeed(i, 800, map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));
		delay(100);

	}
	delay(400);
	for (int i = 7; i <= 12; ++i) {
		Tast.lesen();
		if (i % 2 == 1) Dynamixel.moveSpeed(i, 800, map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));
		delay(100);

	}
	delay(1000);

	for (int i = 13; i <= 18; ++i) {
		Tast.lesen();
		if (i % 2 == 0) Dynamixel.moveSpeed(i, 700, map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));
		delay(100);

	}
	delay(600);
	for (int i = 13; i <= 18; ++i) {
		Tast.lesen();
		if (i % 2 == 1) Dynamixel.moveSpeed(i, 700, map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));
		delay(100);

	}
	delay(800);



	int grundPos[] = {
		512, 512, 512, 512, 512, 512,
		600, 600, 600, 600, 600, 600,
		650, 650, 650, 650, 650, 650
	};

	for (int i = 1; i <= 18; ++i) {
		Tast.lesen();
		if (i % 2 == 0) Dynamixel.moveSpeed(i, grundPos[i - 1], map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));

		delay(100);
	}
	delay(500);
	for (int i = 1; i <= 18; ++i) {
		Tast.lesen();
		if (i % 2 == 1) Dynamixel.moveSpeed(i, grundPos[i - 1], map(Tast.getTasteWert(Poti, true), 0, 128, 10, 512));
		delay(100);

	}

}

bool timo_1(uint32_t intervalWert)
{
	if (timer_1 < millis())
	{
		timer_1 = millis() + (intervalWert);
		return true;
	}
	return false;
}
void AufgabeUmsetzen(Hannah) {

	switch (H.getAufgabe())
	{
	case Null:
		break;
	case Laufen:
		Tast.sendBefehl(Tast.Akku);

		break;
	case Tanzen:

		Tast.sendBefehl(Tast.Online);

		break;
	case Springen:
		break;
	case StartPosi:
		GrundPosition();
		H.AufgabeFertig();
		break;
	case Schlapp:
		for (int i = 1; i <= 18; ++i) {
			Dynamixel.torqueStatus(i, false);
			Tast.sendBefehl(Tast.TESTEN);
		};
		H.setAufgabe(0);
		break;

	case Frost:
		for (int i = 1; i <= 18; ++i) {
			Dynamixel.torqueStatus(i, true);
			Tast.sendBefehl(Tast.TESTEN);
		};
		H.AufgabeFertig();
		break;
	default:
		break;
	}

}

void TastenInterpretieren() {

	/*	Daten die von der Funke kommen*/
	Tast.lesen();

	// auf Tasten reagieren

	if (Tast.ist_offline())
	{
		Serial.println("offline");
	}

	if (Tast.getTasteStatus(TRAINER)) {
		H.setAufgabe(StartPosi);
	}

	if (Tast.getTasteStatus(HL1)) {
		digitalWrite(LED_BUILTIN, HIGH);
		Tast.sendBefehl(Tast.Online);

		//Dynamixel.moveSpeed(1, map(Tast.getTasteWert(HL_LR), 30, 90, 300, 700), map(Tast.getTasteWert(Poti, 1), 0, 128, 10, 254));
		//Dynamixel.moveSpeed(7, map(Tast.getTasteWert(HL_UD), 30, 90, 200, 700), map(Tast.getTasteWert(Poti, 1), 0, 128, 10, 254));

	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
		Tast.sendBefehl(Tast.Akku);
	}

	if (Tast.getTasteStatus(HR1)) {
		// 16 10 4

		/*Dynamixel.moveSpeed(16, Dynamixel.readPosition(13), map(Tast.getTasteWert(Poti, 1), 0, 128, 10, 254));
		Dynamixel.moveSpeed(10, Dynamixel.readPosition(7), map(Tast.getTasteWert(Poti, 1), 0, 128, 10, 254));
		Dynamixel.moveSpeed(4, Dynamixel.readPosition(1), map(Tast.getTasteWert(Poti, 1), 0, 128, 10, 254));*/

	}

	if (Tast.getTasteStatus(T3)) H.setAufgabe(Schlapp);
	if (Tast.getTasteStatus(T2)) H.setAufgabe(Frost);
}