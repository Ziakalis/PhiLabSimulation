#pragma once
#include "ObjectTypedef.h"
#include <malloc.h>
using namespace PhyLabSimu;

struct Field
{
	double xMin, xMax, yMin, yMax, zMin, zMax; //Boundary
	double StrengthX, StrengthY, StrengthZ;
};

class CSceneElement
{
public:
	CSceneElement(PLBaseObject* _pObj, Vector _Pos, Vector _Vel, Vector _Att, Vector _Agv);
	~CSceneElement();
	PLBaseObject* pObj;
	bool Visibility;
	bool isParticle;
	bool isWall;
	Vector Pos;
	Vector Vel;
	Vector Acc;
	Vector Att; //pitch roll yaw
	Vector Agv; //angular velocity
	Vector Aga; //angular accelerate
	Vector Force;
	Vector Moment;

	void KinematicUpdate(double SampleTime);
private:

};

class CScene
{
public:
	bool EnableGravitationalAttraction;
	bool EnableElectromagneticForce;
	double SampleTime;
	double SimuTime;
	double StopTime;
	Field GravityField;
	Field ElectricField;
	Field MagneticField;

	int ObjNum;
	CSceneElement** ppElementList;
	void (*pInitializeSceneFcn)(CScene* pScene);
	void (*pDynamicCalculationFcn)(CScene* pScene);

	CScene(void (*_pInitializeSceneFcn)(CScene*), void (*_pDynamicCalculationFcn)(CScene*));
	~CScene();
	void InitializeScene();
	void DynamicCalculation();
	void KinematicCalculation();
};

