#include "ik.h"
#include <cmath>
#include <math.h>       /* sin */


ik::ik()
{
	//////////////
	// setFeetPosX
	// setFeetPosY
	// setFeetPosZ
/*
	float ergX = 0.0f;
	float ergY = TL;
	float ergZ = 0.0f;

	for (int i = 0; i < 6; ++i)
	{
		switch (i)
		{
		case 0:
			ergX = cosf(60.0f / 180.0f * pia)*(CL + FL);
			ergZ = sinf(60.0f / 180.0f * pia)*(CL + FL);
			break;
		case 1:
			ergX = (CL + FL);
			ergZ = 0.0f;
			break;
		case 2:
			ergX = cosf(60.0f / 180.0f * pia)*(CL + FL);
			ergZ = sinf(-60.0f / 180.0f * pia)*(CL + FL);
			break;
		case 3:
			ergX = -(cosf(60.0f / 180.0f * pia)*(CL + FL));
			ergZ = sinf(-60.0f / 180.0f * pia)*(CL + FL);
			break;
		case 4:
			ergX = -(CL + FL);
			ergZ = 0.0f;
			break;
		case 5:
			ergX = -(cosf(60.0f / 180.0f * pia)*(CL + FL));
			ergZ = sinf(60.0f / 180.0f * pia)*(CL + FL);
			break;
		}
		FeetPosX[i] = ergX;
		FeetPosY[i] = ergY;
		FeetPosZ[i] = ergZ;
	}
*/
// setFeetPosX
// setFeetPosY
// setFeetPosZ
//////////////

}


ik::~ik()
{
}

float ik::getCoxa(uint8_t LN)
{
	// =AA31
	Coxa[LN] = getIKCoxaAngle(LN);
	return Coxa[LN];
}

float ik::getFemur(uint8_t LN)
{
	// =AA30
	Femur[LN] = getIKFemurAngle(LN);
	return Femur[LN];
}

float ik::getTibia(uint8_t LN)
{
	// =AA29 
	Tibia[LN] = getIKTibiaAngle(LN);
	return Tibia[LN];
}

float ik::getIKCoxaAngle(uint8_t LN)
{
	//= 90 - ARCTAN2(AA21; AA22) * 180 / pia()
	float _Q_21 = getTranformX(LN);
	float _Q_22 = getTranformZ(LN);
	IKCoxaAngle[LN] =  ((atan2f(_Q_21, _Q_22) * 180.0f) / pia);
	return IKCoxaAngle[LN];
}


float ik::getIKFemurAngle(uint8_t LN)
{
	//=(AA26+AA27)*180/pia()-90
	float _Q_26 = getIKA1(LN);
	float _Q_27 = getIKA2(LN);

	IKFemurAngle[LN] = ((_Q_26 + _Q_27) * (180.0f / pia)) - 90;
	return IKFemurAngle[LN];
}

float ik::getIKTibiaAngle(uint8_t LN)
{
	// =90-AA28*180/pia()
	float _Q_28 = getTAngle(LN);
	IKTibiaAngle[LN] = 90.0f - (_Q_28 * 180.0f / pia);
	return IKTibiaAngle[LN];
}

float ik::getTAngle(uint8_t LN)
{
	//=ARCCOS((AA25*AA25-C6*C6-C5*C5)/(-2*C5*C6))
	float _Q_25 = getIKSW(LN);
	TAngle[LN] = acosf(((_Q_25*_Q_25) - (TL*TL) - (FL*FL)) / (-2 * FL*TL));
	return TAngle[LN];
}

float ik::getIKA1(uint8_t LN)
{
	//= ARCTAN((AA24 - C4) / AA23)
	float _Q_24 = getCoxaFeetDist(LN);
	float _Q_23 = getTranformY(LN);

	IKA1[LN] = 0.0f;
	if (_Q_23 > 0) 
		IKA1[LN] = atanf((_Q_24 - CL) / _Q_23);
	else if (_Q_23 < 0)
		IKA1[LN] = atan((_Q_24 - CL) / _Q_23) + 180; 
	return IKA1[LN];
}

float ik::getIKA2(uint8_t LN)
{
	// =ARCCOS((C6*C6-C5*C5-AA25*AA25)/(-2*AA25*C5))
	float _Q_25 = getIKSW(LN);
	IKA2[LN] = acosf(((TL*TL) - (FL*FL) - (_Q_25* _Q_25)) / (-2 * _Q_25*FL));
	return IKA2[LN];
}

float ik::getIKSW(uint8_t LN)
{
	// =WURZEL((AA24-C4)*(AA24-C4)+AA23*AA23)
	float _Q_24 = getCoxaFeetDist(LN);
	float _Q_23 = getTranformY(LN);

	IKSW[LN] = sqrt((_Q_24 - CL)*(_Q_24 - CL) + (_Q_23*_Q_23));
	return IKSW[LN];
}

float ik::getCoxaFeetDist(uint8_t LN)
{
	// =WURZEL(AA21*AA21+*AA22)
	float _Q_21 = getTranformX(LN);
	float _Q_22 = getTranformZ(LN);
	CoxaFeetDist[LN] = sqrt((_Q_21*_Q_21) + (_Q_22*_Q_22));
	return CoxaFeetDist[LN];
}

float ik::getTranformX(uint8_t LN)
{
	// =NewPosX*COS(30/180*PI()) -NewPosZ*SIN(30/180*PI())
	float _Q_16 = getNewPosX(LN);
	float _Q_17 = getNewPosZ(LN);
	TranformX[LN] = _Q_16*(cosf((30.0f + (60 * LN)) / 180.0f * pia)) - _Q_17*(sinf((30.0f + (60 * LN)) / 180.0f *pia));
	return TranformX[LN];
}

float ik::getTranformY(uint8_t LN)
{
	//=NewPosY
	TranformY[LN] = getNewPosY(LN);
	return TranformY[LN];
}

float ik::getTranformZ(uint8_t LN)
{
	//=NewPosX*SIN(30/180*pia())+NewPosZ*COS(30/180*pia())
	TranformZ[LN] = getNewPosX(LN)*sinf((30.0f + (60 * LN)) / 180.0f * pia) + getNewPosZ(LN)*cosf((30.0f + (60 * LN)) / 180.0f * pia);
	return TranformZ[LN];
}

float ik::getLegLengthXZ(uint8_t LN)
{
	// =AA24
	LegLengthXZ[LN] = getCoxaFeetDist(LN);
	return LegLengthXZ[LN];
}

float ik::getCoxaStartPosXZ(uint8_t LN)
{
	// =F17
	// CenterXmm
	CoxaStartPosXZ[LN] = CenterX;
	return CoxaStartPosXZ[LN];
}

float ik::getCoxaEndPosXZ(uint8_t LN)
{
	// =C4
	CoxaEndPosXZ[LN] = CL;
	return CoxaEndPosXZ[LN];
}

float ik::getCoxaStartPosY(uint8_t LN)
{
	// =R28

	CoxaStartPosY[LN] = getFeetPosY(LN);
	return CoxaStartPosY[LN];
}

float ik::getCoxaEndPosY(uint8_t LN)
{
	// =R28 
	CoxaEndPosY[LN] = getFeetPosY(LN);
	return CoxaEndPosY[LN];
}

float ik::getFemurStartPosXZ(uint8_t LN)
{
	// =R17
	FemurStartPosXZ[LN] = getCoxaEndPosXZ(LN);
	return FemurStartPosXZ[LN];
}

float ik::getFemurEndPosXZ(uint8_t LN)
{
	// =C5*COS(R4*pia()/180)+R20
	FemurEndPosXZ[LN] = FL*cosf(getFemur(LN) * pia / 180.0f) + getFemurStartPosXZ(LN);
	return FemurEndPosXZ[LN];
}


float ik::getFemurStartPosY(uint8_t LN)
{
	// =R15
	FemurStartPosY[LN] = getCoxaEndPosY(LN);
	return FemurStartPosY[LN];
}
float ik::getFemurEndPosY(uint8_t LN)
{
	// =R18 - C5*SIN(R4*pia()/180)
	FemurEndPosY[LN] = getFemurStartPosY(LN) - FL*sinf(getFemur(LN)*pia / 180.0f);
	return FemurEndPosY[LN];
}

float ik::getTibiaStartPosXZ(uint8_t LN)
{
	// =R21
	TibiaStartPosXZ[LN] = getFemurEndPosXZ(LN);
	return TibiaStartPosXZ[LN];
}

float ik::getTibiaEndPosXZ(uint8_t LN)
{
	// =R24-SIN(R5*pia()/180)*C6
	TibiaEndPosXZ[LN] = getTibiaStartPosXZ(LN) - sinf(Tibia[LN] * pia / 180.0f)*TL;
	return TibiaEndPosXZ[LN];
}

float ik::getTibiaStartPosY(uint8_t LN)
{
	// =R19
	TibiaStartPosY[LN] = getFemurEndPosY(LN);
	return TibiaStartPosY[LN];
}

float ik::getTibiaEndPosY(uint8_t LN)
{
	// =R19-C6*COS(R5*pia()/180)
	TibiaEndPosY[LN] = getFemurEndPosY(LN) - TL*cosf(FL * pia / 180.0f);
	return TibiaEndPosY[LN];
}

float ik::getFeetPosX(uint8_t LN)
{
	// =NewPosX+I2
	float  tempX = 0.0f;
	switch (LN)
	{
	case 0:tempX = COXABODYCENTEROFFSETX1; break;
	case 1:tempX = COXABODYCENTEROFFSETX2; break;
	case 2:tempX = COXABODYCENTEROFFSETX3; break;
	case 3:tempX = COXABODYCENTEROFFSETX4; break;
	case 4:tempX = COXABODYCENTEROFFSETX5; break;
	case 5:tempX = COXABODYCENTEROFFSETX6; break;
	}
	FeetPosX[LN] = getNewPosX(LN) + (tempX);
	return FeetPosX[LN];
}

float ik::getFeetPosY(uint8_t LN)
{
	// =NewPosY
	FeetPosY[LN] = getNewPosY(LN);
	return FeetPosY[LN];
}

float ik::getFeetPosZ(uint8_t LN)
{
	// =NewPosZ+J2
	float  tempZ = 0.0f;
	switch (LN)
	{
	case 0:tempZ = COXABODYCENTEROFFSETZ1; break;
	case 1:tempZ = COXABODYCENTEROFFSETZ2; break;
	case 2:tempZ = COXABODYCENTEROFFSETZ3; break;
	case 3:tempZ = COXABODYCENTEROFFSETZ4; break;
	case 4:tempZ = COXABODYCENTEROFFSETZ5; break;
	case 5:tempZ = COXABODYCENTEROFFSETZ6; break;
	}
	FeetPosZ[LN] = getNewPosZ(LN) + tempZ;
	return FeetPosZ[LN];
}

uint8_t ik::getGaitStepCur(uint8_t GSC)
{
	//= WENN(Q40 = 3; D57; WENN(Q40 = 4; E57; WENN(Q40 = 5; F57; WENN(Q40 = 6; G57; 0))))
	//for (int i = 0; i < 6; ++i) GaitStepCur[i] = 0.0f;
	//for (int GSC = 0; GSC < 6; ++GSC)
	GaitStepCur[GSC] = LegSeque[GSC][getGaitStep()];

	return GaitStepCur[GSC];
}
float ik::getTotalX(uint8_t LN)
{
	// =I12+I2+PosX+C49
	// =J12+I3+PosX+G49
	// =K12+I4+PosX+E49
	// =L12+I5+PosX-B49
	// =M12+I6+PosX-D49
	// =N12+I7+PosX-F49
	// CGEBDF

	float  tempX = 0.0f;

	switch (LN)
	{// 153024  
	case 0:tempX = COXABODYCENTEROFFSETX1; break;
	case 1:tempX = COXABODYCENTEROFFSETX2; break;
	case 2:tempX = COXABODYCENTEROFFSETX3; break;
	case 3:tempX = COXABODYCENTEROFFSETX4; break;
	case 4:tempX = COXABODYCENTEROFFSETX5; break;
	case 5:tempX = COXABODYCENTEROFFSETX6; break;
	}
	TotalX[LN] = FeetPosX_WRT_COXA[LN] + tempX + getPosX() + getGaitPosX(LegNum[LN]);

	return TotalX[LN];
}

float ik::getTotalZ(uint8_t LN)
{
	// =I14+J2+PosZ+C51
	// =J14+J3+PosZ+G51
	// =K14+J4+PosZ+E51
	// =L14+J5+PosZ+B51
	// =M14+J6+PosZ+D51
	// =N14+J7+PosZ+F51
	// 
	// CGEBDF
	float  tempZ = 0.0f;

	switch (LN)
	{
	case 0:tempZ = COXABODYCENTEROFFSETZ1; break;
	case 1:tempZ = COXABODYCENTEROFFSETZ2; break;
	case 2:tempZ = COXABODYCENTEROFFSETZ3; break;
	case 3:tempZ = COXABODYCENTEROFFSETZ4; break;
	case 4:tempZ = COXABODYCENTEROFFSETZ5; break;
	case 5:tempZ = COXABODYCENTEROFFSETZ6; break;
	}

	TotalZ[LN] = FeetPosZ_WRT_COXA[LN] + tempZ + getPosZ() + getGaitPosZ(LegNum[LN]);
	return TotalZ[LN];
}

float ik::getTotalY(uint8_t LN)
{
	//=I13+C50
	TotalY[LN] = FeetPosY_WRT_COXA[LN] + getGaitPosY(LegNum[LN]);
	return TotalY[LN];
}

float ik::getsinRotX(uint8_t LN)
{
	// =SIN(RotX*pia()/180)
	sinRotX[LN] = sinf(getRotX()*pia / 180.0f);
	return sinRotX[LN];
}

float ik::getcosRotX(uint8_t LN)
{
	//=COS(RotX*pia()/180)
	cosRotX[LN] = cosf(getRotX()*pia / 180.0f);
	return cosRotX[LN];
}

float ik::getsinRotZ(uint8_t LN)
{
	//=SIN(RotZ*pia()/180)
	sinRotZ[LN] = sinf(getRotZ()*pia / 180.0f);
	return sinRotZ[LN];
}

float ik::getcosRotZ(uint8_t LN)
{
	//=COS(RotZ*pia()/180)
	cosRotZ[LN] = cosf((getRotZ()*pia) / 180.0f);
	return cosRotZ[LN];
}

float ik::getsinRotY_rotationY(uint8_t LN)
{
	//=SIN(RotY*pia()/180)
	sinRotY_rotationY[LN] = sinf((getRotY() * pia) / 180.0f);
	return sinRotY_rotationY[LN];
}

float ik::getcosRotY_rotationY(uint8_t LN)
{
	// =COS(RotY*pia()/180)
	cosRotY_rotationY[LN] = cosf((getRotY()*pia) / 180.0f);
	return cosRotY_rotationY[LN];
}

float ik::getBodyIkX(uint8_t LN)
{
	float _Q_4 = getTotalX(LN);
	float _Q_5 = getTotalZ(LN);
	float _Q_6 = getTotalY(LN);
	//float _Q_7 = getsinRotX(LN);
	//float _Q_8 = getcosRotX(LN);
	float _Q_9 = getsinRotZ(LN);
	float _Q_10 = getcosRotZ(LN);
	float _Q_11 = getsinRotY_rotationY(LN);
	float _Q_12 = getcosRotY_rotationY(LN);
	//=TotalX*cos_rotZ*cos_rotY + rotationY_-TotalZ*cos_rotZ*sin_rotY + rotationY_+TotalY*sin_rotZ - TotalX
	BodyIkX[LN] = (_Q_4*_Q_10*_Q_12) - (_Q_5*_Q_10*_Q_11) + (_Q_6*_Q_9) - _Q_4;
	return BodyIkX[LN];
}

float ik::getBodyIkZ(uint8_t LN)
{
	float _Q_4 = getTotalX(LN);
	float _Q_5 = getTotalZ(LN);
	float _Q_6 = getTotalY(LN);
	float _Q_7 = getsinRotX(LN);
	float _Q_8 = getcosRotX(LN);
	float _Q_9 = getsinRotZ(LN);
	float _Q_10 = getcosRotZ(LN);
	float _Q_11 = getsinRotY_rotationY(LN);
	float _Q_12 = getcosRotY_rotationY(LN);
	// =(TotalX*cos_rotX*sin_rotY + rotationY_+TotalX*cos_rotY + rotationY_*sin_rotZ*sin_rotX+TotalZ*cos_rotY + rotationY_*cos_rotX-TotalZ*sin_rotY + rotationY_*sin_rotZ*sin_rotX-TotalY*cos_rotZ*sin_rotX)-TotalZ
	BodyIkZ[LN] = ((_Q_4*_Q_8*_Q_11) + (_Q_4*_Q_12*_Q_9*_Q_7) + (_Q_5*_Q_12*_Q_8) - (_Q_5*_Q_11*_Q_9*_Q_7) - (_Q_6*_Q_10*_Q_7)) - _Q_5;
	return BodyIkZ[LN];
}

float ik::getBodyIkY(uint8_t LN)
{
	// = (            TotalX       *     sin_rotY + rotationY_               *    sin_rotX        -   TotalX        *     cos_rotY + rotationY_               *     cos_rotX      *      sin_rotZ      +      TotalZ     *           cos_rotY + rotationY_         *         sin_rotX   +       TotalZ    *       cos_rotX    *           sin_rotY + rotationY_         *   sin_rotZ         +     TotalY      *   cos_rotZ       *     cos_rotX)       -    TotalY
	float _Q_4 = getTotalX(LN);
	float _Q_5 = getTotalZ(LN);
	float _Q_6 = getTotalY(LN);
	float _Q_7 = getsinRotX(LN);
	float _Q_8 = getcosRotX(LN);
	float _Q_9 = getsinRotZ(LN);
	float _Q_10 = getcosRotZ(LN);
	float _Q_11 = getsinRotY_rotationY(LN);
	float _Q_12 = getcosRotY_rotationY(LN);
	//= (TotalX*sin_rotY + rotationY_*sin_rotX - TotalX*cos_rotY + rotationY_*cos_rotX*sin_rotZ + TotalZ*cos_rotY + rotationY_*sin_rotX + TotalZ*cos_rotX*sin_rotY + rotationY_*sin_rotZ + TotalY*cos_rotZ*cos_rotX) - TotalY
	BodyIkY[LN] = ((_Q_4*_Q_11*_Q_7) - (_Q_4*_Q_12*_Q_8*_Q_9) + (_Q_5*_Q_12*_Q_7) + (_Q_5*_Q_8*_Q_11*_Q_9) + (_Q_6*_Q_10*_Q_8)) - _Q_6;
	return BodyIkY[LN];
}

float ik::getNewPosX(uint8_t LN)
{
	// =I12+AA13+B49+PosX
	NewPosX[LN] = FeetPosX_WRT_COXA[LN];
	NewPosX[LN] += getBodyIkX(LN);
	NewPosX[LN] += getGaitPosX(LN);
	NewPosX[LN] += getPosX();

	// Wundersamm Rechen fehler hmmmm...  auf mal verschwunden ... sonst Delay notwendig
	// delay(1);

	return NewPosX[LN];
}

float ik::getNewPosY(uint8_t LN)
{
	// =I13+AA15+B50+PosY
	NewPosY[LN] = FeetPosY_WRT_COXA[LN] + getBodyIkY(LN) + getGaitPosY(LN) + getPosY();
	return NewPosY[LN];
}

float ik::getNewPosZ(uint8_t LN)
{
	// =I14+AA14+B51+PosZ
	NewPosZ[LN] = FeetPosZ_WRT_COXA[LN] + getBodyIkZ(LN) + getGaitPosZ(LN) + getPosZ();
	return NewPosZ[LN];
}

bool ik::getStepLegNr(uint8_t G_Step)
{
	//=WENN(Q40 = G40 +1  ; 1;0)
	uint8_t temp = getGaitStep();
	//for (int i = 0; i < 6; ++i)
	//{
	//	if (LegSequence[i] == temp) StepLegNr[i] = true;
	//	else StepLegNr[i] = false;
	//}

	if (LegSequence[G_Step] == temp) StepLegNr[G_Step] = true;
	else StepLegNr[G_Step] = false;

	return StepLegNr[G_Step];
}

bool ik::getStepLegNrAdd1(uint8_t G_Step)
{
	uint8_t temp = getGaitStep();
	//for (int i = 0; i < 6; ++i)
	//{
	//	if (LegSequence[i] == temp - 1) StepLegNrAdd1[i] = true;
	//	else StepLegNrAdd1[i] = false;
	//}
	if (LegSequence[G_Step] == temp - 1) StepLegNrAdd1[G_Step] = true;
	else StepLegNrAdd1[G_Step] = false;

	return StepLegNrAdd1[G_Step];
}

bool ik::getStepLegNrRem5(uint8_t G_Step)
{
	// =WENN(Q40=G40-5;1;0)
	uint8_t temp = getGaitStep();
	//for (int i = 0; i < 6; ++i)
	//{
	//	if (LegSequence[i] == temp + 5) StepLegNrRem5[i] = true;
	//	else StepLegNrRem5[i] = false;
	//}

	if (LegSequence[G_Step] == temp + 5) StepLegNrRem5[G_Step] = true;
	else StepLegNrRem5[G_Step] = false;


	return StepLegNrRem5[G_Step];
}

float ik::getGaitPosX(uint8_t GPX)
{
	///=WENN(G41=1;0;   
	//WENN(ODER(G42=1;G43=1);C41/2;C41/2-I57*C41/4))

	if (getStepLegNr(GPX))
		GaitPosX[GPX] = 0.0f;
	else
		if ((getStepLegNrAdd1(GPX)) || (getStepLegNrRem5(GPX)))
			GaitPosX[GPX] = (TravelLengthX / 2.0f);
		else
			GaitPosX[GPX] = (+(TravelLengthX / 2.0f) - (getGaitStepCur(GPX) * TravelLengthX) / 4.0f);
	return GaitPosX[GPX];
}

float ik::getGaitPosY(uint8_t GPY)
{	// =WENN(G41=1;-C40;0)
	if (getStepLegNr(GPY))GaitPosY[GPY] = -(LegLiftHeight);
	else GaitPosY[GPY] = 0.0f;
	return GaitPosY[GPY];
}

float ik::getGaitPosZ(uint8_t GPZ)
{	// =WENN(G41=1;0;
	//      WENN(ODER(G42=1;G43=1);C42/2;C42/2-I57*C42/4))
	if (getStepLegNr(GPZ))
		GaitPosZ[GPZ] = 0.0f;
	else
		if (getStepLegNrAdd1(GPZ) || getStepLegNrRem5(GPZ))
			GaitPosZ[GPZ] = TravelLengthZ / 2.0f;
		else
			GaitPosZ[GPZ] = TravelLengthZ / 2.0f - getGaitStepCur(GPZ)*TravelLengthZ / 4.0f;

	return GaitPosZ[GPZ];
}

float ik::getGaitRotY(uint8_t GRY)
{
	// =WENN(G41=1;0;WENN(ODER(G42=1;G43=1);C43/2;C43/2-I57*C43/4))

	if (getStepLegNr(GRY))
		GaitRotY[GRY] = 0.0f;
	else if (getStepLegNrAdd1(GRY) || getStepLegNrRem5(GRY))
		GaitRotY[GRY] = TravelRotationY / 2.0f;
	else
		GaitRotY[GRY] = TravelRotationY / 2.0f - getGaitStepCur(GRY)* TravelRotationY / 4.0f;
	return GaitRotY[GRY];
}


//Direkte Kinematik


ik IK;