#include "Scene.h"

CSceneElement::CSceneElement(PLBaseObject* _pObj, Vector _Pos, Vector _Vel, Vector _Att, Vector _Agv)
{
	Vector ZeroVec = { 0,0,0 };
	Visibility = true;
	isParticle = true;
	pObj = _pObj;
	Pos = _Pos;
	Vel = _Vel;
	Att = _Att;
	Agv = _Agv;
	Acc = ZeroVec;
	Aga = ZeroVec;
	Force = ZeroVec;
	Moment = ZeroVec;
}

CSceneElement::~CSceneElement()
{
	if (!pObj)
		free(pObj);
}

void CSceneElement::KinematicUpdate(double SampleTime)
{
	Acc = VecScale(Force, 1.0f / pObj->Mass);
	Vel = VecAdd(Vel, VecScale(Acc, SampleTime));
	Pos = VecAdd(Pos, VecScale(Vel, SampleTime));

	if (!isParticle)
	{
		//TODO: Use Quaternion to Calculate the Attitude
	}
}

CScene::CScene(void (*_pInitializeSceneFcn)(CScene*), void (*_pDynamicCalculationFcn)(CScene*))
{
	EnableGravitationalAttraction = false;
	EnableElectromagneticForce = false;
	SampleTime = 1.0f;
	SimuTime = 0.0f;
	StopTime = 1000.0f;
	memset(&GravityField, 0, sizeof(GravityField));
	memset(&ElectricField, 0, sizeof(ElectricField));
	memset(&MagneticField, 0, sizeof(MagneticField));

	ObjNum = 0;
	ppElementList = NULL;
	pInitializeSceneFcn = _pInitializeSceneFcn;
	pDynamicCalculationFcn = _pDynamicCalculationFcn;
}

CScene::~CScene()
{
	if (ppElementList)
	{
		for (int i = 0; i < ObjNum; i++)
		{
			if (ppElementList[i]->pObj)
			{
				delete ppElementList[i]->pObj;
			}
		}
		free(ppElementList);
	}
}

void CScene::InitializeScene()
{
	if (pInitializeSceneFcn)
	{
		(*pInitializeSceneFcn)(this);
	}
}
void CScene::DynamicCalculation()
{
	if (pDynamicCalculationFcn)
	{
		(*pDynamicCalculationFcn)(this);
	}
}

void CScene::KinematicCalculation()
{
	for (int i = 0; i < ObjNum; i++)
	{
		if (!ppElementList[i]->isWall)
		{
			ppElementList[i]->KinematicUpdate(SampleTime);
		}
	}
	SimuTime += SampleTime;
}