#include "CustomScene.h"

void InitializeMainScene(CScene* pScene)
{
	//SolarEarthInit(pScene);
	SpringBallsInitial(pScene);
}

void DynamicCalculation(CScene* pScene)
{
	//SolarEathDynamic(pScene);
	SpringBallsDynamic(pScene);
}

void SolarEarthInitial(CScene* pScene)
{
	PLBall* Earth = new PLBall(5.965e24, 6378137.0);
	PLBall* Sun = new PLBall(1.9891e30, 6.955e5);
	Vector EarthPos;
	Vector EarthVel;
	Vector ZeroVec;

	EarthPos.x = 149600000000.0;
	EarthPos.y = 0.0;
	EarthPos.z = 0.0;

	EarthVel.x = 0.0;
	EarthVel.y = 29770.0593983;
	EarthVel.z = 0.0;

	memset(&ZeroVec, 0, sizeof(ZeroVec));

	pScene->ObjNum = 2;
	pScene->EnableGravitationalAttraction = true;
	pScene->SampleTime = 3600.0;
	pScene->StopTime = 800.0 * 24.0 * 3600.0;
	pScene->ppElementList = (CSceneElement * *)malloc(sizeof(CSceneElement*) * pScene->ObjNum);
	if (pScene->ppElementList)
	{
		pScene->ppElementList[0] = new CSceneElement(Earth, EarthPos, EarthVel, ZeroVec, ZeroVec);
		pScene->ppElementList[1] = new CSceneElement(Sun, ZeroVec, ZeroVec, ZeroVec, ZeroVec);
	}
}

void SolarEarthDynamic(CScene* pScene)
{
	Vector ZeroVec;
	memset(&ZeroVec, 0, sizeof(ZeroVec));

	Vector RSE = VecSub(pScene->ppElementList[0]->Pos, pScene->ppElementList[1]->Pos);
	double dist = VecNorm(RSE);
	double force = M_PL_GRAVITATIONAL_FORCE_CONST * pScene->ppElementList[0]->pObj->Mass / dist * pScene->ppElementList[1]->pObj->Mass / dist;
	Vector EarthForce = VecScale(VecScale(RSE, -1.0f / dist), force);

	pScene->ppElementList[0]->Force = EarthForce;
	pScene->ppElementList[0]->Moment = ZeroVec;
	pScene->ppElementList[1]->Force = VecScale(EarthForce, -1.0f);
	pScene->ppElementList[1]->Moment = ZeroVec;
}

void SpringBallsInitial(CScene* pScene)
{
	PLBall* Ball0 = new PLBall(1, 0.2);
	PLBall* Ball1 = new PLBall(2, 0.25);
	Vector Pos0, Pos1, Vel0, Vel1;
	Vector ZeroVec;

	Pos0.x = 0.0;
	Pos0.y = 0.0;
	Pos0.z = 0.0;

	Pos1.x = 0.8;
	Pos1.y = 0.0;
	Pos1.z = 0.0;

	Vel0.x = 3.2;
	Vel0.y = 0.0;
	Vel0.z = 0.0;

	Vel1.x = -1.6;
	Vel1.y = 0.0;
	Vel1.z = 0.0;

	memset(&ZeroVec, 0, sizeof(ZeroVec));

	pScene->ObjNum = 2;
	pScene->EnableGravitationalAttraction = false;
	pScene->SampleTime = 0.001;
	pScene->StopTime = 100;
	pScene->ppElementList = (CSceneElement * *)malloc(sizeof(CSceneElement*) * pScene->ObjNum);
	if (pScene->ppElementList)
	{
		pScene->ppElementList[0] = new CSceneElement(Ball0, Pos0, Vel0, ZeroVec, ZeroVec);
		pScene->ppElementList[1] = new CSceneElement(Ball1, Pos1, Vel1, ZeroVec, ZeroVec);
	}
}

void SpringBallsDynamic(CScene* pScene)
{
	Vector ZeroVec;
	memset(&ZeroVec, 0, sizeof(ZeroVec));
	double SpringLen = 0.8;
	double K = 500.0;

	Vector R01 = VecSub(pScene->ppElementList[1]->Pos, pScene->ppElementList[0]->Pos);
	double dist = VecNorm(R01);
	double force = (dist - SpringLen) * K;
	Vector Force01 = VecScale(VecScale(R01, 1.0f / dist), force);

	pScene->ppElementList[0]->Force = Force01;
	pScene->ppElementList[0]->Moment = ZeroVec;
	pScene->ppElementList[1]->Force = VecScale(Force01, -1.0f);
	pScene->ppElementList[1]->Moment = ZeroVec;
}
