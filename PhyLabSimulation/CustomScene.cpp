#include "CustomScene.h"

void InitializeMainScene(CScene* pScene)
{
	PLBall* Earth = new PLBall(5.965e24, 6378137.0);
	PLBall* Sun = new PLBall(1.9891e30, 6.955e5);
	Vector EarthPos;
	Vector EarthVel;
	Vector ZeroVec;

	EarthPos.x = 149600000000.0;
	EarthPos.y = 0.0f;
	EarthPos.z = 0.0f;

	EarthVel.x = 0.0f;
	EarthVel.y = 29770.0593983;
	EarthVel.z = 0.0f;

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

void DynamicCalculation(CScene* pScene)
{
	Vector ZeroVec;
	memset(&ZeroVec, 0, sizeof(ZeroVec));

	Vector RSE = VecSub(pScene->ppElementList[0]->Pos, pScene->ppElementList[1]->Pos);
	double dist = VecNorm(RSE);
	double force = M_PL_GRAVITATIONAL_FORCE_CONST * pScene->ppElementList[0]->pObj->Mass /dist * pScene->ppElementList[1]->pObj->Mass / dist;
	Vector EarthForce = VecScale(VecScale(RSE, -1.0f / dist), force);
	
	pScene->ppElementList[0]->Force = EarthForce;
	pScene->ppElementList[0]->Moment = ZeroVec;
	pScene->ppElementList[1]->Force = VecScale(EarthForce, -1.0f);
	pScene->ppElementList[1]->Moment = ZeroVec;
}