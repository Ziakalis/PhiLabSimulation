#pragma once
#include "Scene.h"
#include "ObjectTypedef.h"
#include "ConstDefines.h"
#include <malloc.h>
using namespace PhyLabSimu;

void InitializeMainScene(CScene* pScene);
void DynamicCalculation(CScene* pScene);



//Example1:
void SolarEarthInitial(CScene* pScene);
void SolarEarthDynamic(CScene* pScene);

//Example2:
void SpringBallsInitial(CScene* pScene);
void SpringBallsDynamic(CScene* pScene);