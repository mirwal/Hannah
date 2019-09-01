#pragma once
#include <Arduino.h>
#include <cmath>
#define DEBUG(x)	Serial.print(x)
float const pia = 3.1415926535897932384626433832795f;

#define SL				232.0		//Seitenlänge des Body's
#define	CL				50.0		//Coxa Length
#define	FL				64.2		//Femur Length
#define	TL				94.8		//Tibia Length
#define OFFTL			-20

#define BODYCOXAOFFSETX	(SL/2.0)
#define BODYCOXAOFFSETZ (sqrt(((SL*SL)-(BODYCOXAOFFSETX*BODYCOXAOFFSETX))))
#define BODYCOXAOFFSET	(SL)

#define COXABODYCENTEROFFSETX1	(BodyCoxaOffsetX) 
#define COXABODYCENTEROFFSETX2	(BODYCOXAOFFSET)
#define COXABODYCENTEROFFSETX3	(BodyCoxaOffsetX)
#define COXABODYCENTEROFFSETX4	(BodyCoxaOffsetX * (-1))
#define COXABODYCENTEROFFSETX5	(BODYCOXAOFFSET * (-1))
#define COXABODYCENTEROFFSETX6	(BodyCoxaOffsetX * (-1))

#define COXABODYCENTEROFFSETZ1	(BodyCoxaOffsetZ) 
#define COXABODYCENTEROFFSETZ2	(0.0f)
#define COXABODYCENTEROFFSETZ3	(BodyCoxaOffsetZ * (-1))
#define COXABODYCENTEROFFSETZ4	(BodyCoxaOffsetZ * (-1))
#define COXABODYCENTEROFFSETZ5	(0.0f)
#define COXABODYCENTEROFFSETZ6	(BodyCoxaOffsetZ)



class ik
{
public:
	ik();
	~ik();
	typedef unsigned char uint8_t;
	//cgebdf	//153024
	uint8_t LegNum[6] = {1,5,3,0,2,4 };// { 1, 5, 3, 0, 2, 4 };
	//uint8_t LegNumTotal_Test[6] = { 1,5,3,0 ,2,4 };// { 1, 5, 3, 0, 2, 4 };
	
	/////////////
	// Leg Angles
	float Coxa[6] = { 0.0f };
	float Femur[6] = { 0.0f };
	float Tibia[6] = { 0.0f };
	float getCoxa(uint8_t LN);
	float getFemur(uint8_t LN);
	float getTibia(uint8_t LN);
	

	////////
	//Leg IK
	float IKCoxaAngle[6] = { 0.0f };
	float getIKCoxaAngle(uint8_t LN);
	float IKFemurAngle[6] = { 0.0f };
	float getIKFemurAngle(uint8_t LN);
	float IKTibiaAngle[6] = { 0.0f };
	float getIKTibiaAngle(uint8_t LN);
	float TAngle[6] = { 0.0f };
	float getTAngle(uint8_t LN);
	float IKA1[6] = { 0.0f };
	float getIKA1(uint8_t LN);

	float IKA2[6] = { 0.0f };
	float getIKA2(uint8_t LN);
	float IKSW[6] = { 0.0f };
	float getIKSW(uint8_t LN);
	float CoxaFeetDist[6] = { 0.0f };
	float getCoxaFeetDist(uint8_t LN);
	float TranformX[6] = { 0.0f };
	float getTranformX(uint8_t LN);
	float TranformY[6] = { 0.0f };
	float getTranformY(uint8_t LN);
	float TranformZ[6] = { 0.0f };
	float getTranformZ(uint8_t LN);

	//////////////
	//Display Data
	float LegLengthXZ[6] = { 0.0f };
	float getLegLengthXZ(uint8_t LN);
	float CoxaStartPosXZ[6] = { 0.0f };
	float getCoxaStartPosXZ(uint8_t LN);
	float CoxaStartPosY[6] = { 0.0f };
	float getCoxaStartPosY(uint8_t LN);
	float CoxaEndPosXZ[6] = { 0.0f };
	float getCoxaEndPosXZ(uint8_t LN);
	float CoxaEndPosY[6] = { 0.0f };
	float getCoxaEndPosY(uint8_t LN);
	float FemurStartPosXZ[6] = { 0.0f };
	float getFemurStartPosXZ(uint8_t LN);
	float FemurStartPosY[6] = { 0.0f };
	float getFemurStartPosY(uint8_t LN);
	float FemurEndPosXZ[6] = { 0.0f };
	float getFemurEndPosXZ(uint8_t LN);
	float FemurEndPosY[6] = { 0.0f };
	float getFemurEndPosY(uint8_t LN);
	float TibiaStartPosXZ[6] = { 0.0f };
	float getTibiaStartPosXZ(uint8_t LN);
	float TibiaStartPosY[6] = { 0.0f };
	float getTibiaStartPosY(uint8_t LN);
	float TibiaEndPosXZ[6] = { 0.0f };
	float getTibiaEndPosXZ(uint8_t LN);
	float TibiaEndPosY[6] = { 0.0f };
	float getTibiaEndPosY(uint8_t LN);
	float FeetPosX[6] = { 0.0f };
	float getFeetPosX(uint8_t LN);
	float FeetPosY[6] = { 0.0f };
	float getFeetPosY(uint8_t LN);
	float FeetPosZ[6] = { 0.0f };
	float getFeetPosZ(uint8_t LN);
	
	///////////////////
	// initFeetPosition
	float FeetPosX_WRT_COXA[6] = {
		+(cosf(60 / 180.0f * pia)*(CL + FL)),
		+(CL + FL),
		+(cosf(60 / 180.0f * pia)*(CL + FL)),
		-(cosf(60 / 180.0f * pia)*(CL + FL)),
		-(CL + FL),
		-(cosf(60 / 180.0f * pia)*(CL + FL))
	};
	float FeetPosY_WRT_COXA[6] = { TL + OFFTL,TL + OFFTL,TL + OFFTL,TL + OFFTL,TL + OFFTL,TL + OFFTL };
	float FeetPosZ_WRT_COXA[6] = {
		sinf(60 / 180.0f * pia)*(CL + FL),
		0.0f,
		sinf(-60 / 180.0f * pia)*(CL + FL),
		sinf(-60 / 180.0f * pia)*(CL + FL),
		0.0f,
		sinf(60 / 180.0f * pia)*(CL + FL)
	};
	//////////////////////
	// Center X Z Y  in mm
	float CenterX = 0.0f;
	float CenterZ = 0.0f;
	float CenterY = TL;
	
	/////////
	// Inputs
	float getPosX() { return PosX; }
	float getPosY() { return PosY; }
	float getPosZ() { return PosZ; }
	float getRotX() { return RotX; }
	float getRotY() { return RotY; }
	float getRotZ() { return RotZ; }

	void setPosX(float PX) { PosX = PX; }
	void setPosY(float PY) { PosY = PY; }
	void setPosZ(float PZ) { PosZ = PZ; }
	void setRotX(float RX) { RotX = RX; }
	void setRotY(float RY) { RotY = RY; }
	void setRotZ(float RZ) { RotZ = RZ; }

	float const BodyCoxaOffsetZ = BODYCOXAOFFSETZ;
	float const BodyCoxaOffsetX = BODYCOXAOFFSETX;

	/////////////
	// Gait Setup
	float LegLiftHeight = 0.0f;
	float TravelLengthX = 0.0f;
	float TravelLengthZ = 0.0f;
	float TravelRotationY = 0.0f;
	// Gait Setup
	/////////////


	/////////////
	// Conidtions
	int const LegSequence[6] = { 0,1,2,3,4,5 };

	bool StepLegNr[6] = { true,false,  false, false, false, false };
	bool StepLegNrAdd1[6] = { false,false, false,false,false,false };
	bool StepLegNrRem5[6] = { false,false,false,false,false,true };
	bool getStepLegNr(uint8_t G_Step);
	bool getStepLegNrAdd1(uint8_t G_Step);
	bool getStepLegNrRem5(uint8_t G_Step);

	// Conidtions
	/////////////

	void AddGaitStep() { (GaitStep < 5) ? (++GaitStep) : (GaitStep = 0); }
	void removeGaitStep() { (GaitStep > 0) ? (--GaitStep) : (GaitStep = 5); }
	uint8_t getGaitStep() { return GaitStep; }

	float getGaitPosX(uint8_t GPX);
	float getGaitPosY(uint8_t GPY);
	float getGaitPosZ(uint8_t GPZ);
	float getGaitRotY(uint8_t GRY);

	void setTotalX(uint8_t TX) {
		TotalX[TX] = FeetPosX[TX] + COXABODYCENTEROFFSETX1 + PosX + getGaitPosX(TX);
	}

	float NewPosX[6] = { 0.0f };
	float getNewPosX(uint8_t LN);
	float NewPosY[6] = { 0.0f };
	float getNewPosY(uint8_t LN);
	float NewPosZ[6] = { 0.0f };
	float getNewPosZ(uint8_t LN);

	uint8_t GaitStep = 0;
	float GaitPosX[6] = { 0.0f };
	float GaitPosY[6] = { 0.0f };
	float GaitPosZ[6] = { 0.0f };
	float GaitRotY[6] = { 0.0f };
	/////////////
	// For Calculating Gait pos
	uint8_t GaitStepCur[6] ={ 0,0,1,2,3,4 };// { 0,4,3,2,1,0 };//
	uint8_t const LegSeque[6][6]{
		{ 0,0,1,2,3,4 },
		{ 4,0,0,1,2,3 },
		{ 3,4,0,0,1,2 },
		{ 2,3,4,0,0,1 },
		{ 1,2,3,4,0,0 },
		{ 0,1,2,3,4,0 }
	};
	uint8_t getGaitStepCur(uint8_t GSC);
	// For Calculating Gait pos
	/////////////


	float PosX = 0.0f;
	float PosY = 0.0f;
	float PosZ = 0.0f;

	float RotX = 0.0f;
	float RotY = 0.0f;
	float RotZ = 0.0f;
	////////
	//BodyIK
	float TotalX[6] = { 0.0f };
	float getTotalX(uint8_t LN);
	float TotalZ[6] = { 0.0f };
	float getTotalZ(uint8_t LN);
	float TotalY[6] = { 0.0f };
	float getTotalY(uint8_t LN);


	float sinRotX[6] = { 0.0f };
	float getsinRotX(uint8_t LN);
	float cosRotX[6] = { 0.0f };
	float getcosRotX(uint8_t LN);
	float sinRotZ[6] = { 0.0f };
	float getsinRotZ(uint8_t LN);
	float cosRotZ[6] = { 0.0f };
	float getcosRotZ(uint8_t LN);

	float sinRotY_rotationY[6] = { 0.0f };
	float getsinRotY_rotationY(uint8_t LN);
	float cosRotY_rotationY[6] = { 0.0f };
	float getcosRotY_rotationY(uint8_t LN);
	float BodyIkX[6] = { 0.0f };
	float getBodyIkX(uint8_t LN);
	float BodyIkZ[6] = { 0.0f };
	float getBodyIkZ(uint8_t LN);
	float BodyIkY[6] = { 0.0f };
	float getBodyIkY(uint8_t LN);
	//BodyIK
	////////
private:
};

extern ik IK;
