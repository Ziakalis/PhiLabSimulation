#include "ObjectTypedef.h"
using namespace PhyLabSimu;
/*=================== Vector and Tensor Functions =====================*/
Vector PhyLabSimu::VecAdd(Vector a, Vector b)
{
	Vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vector PhyLabSimu::VecSub(Vector a, Vector b)
{
	Vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

Vector PhyLabSimu::VecMul(Vector a, Vector b)
{
	Vector c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}

Vector PhyLabSimu::VecDiv(Vector a, Vector b)
{
	Vector c;
	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
	return c;
}

double PhyLabSimu::VecDot(Vector a, Vector b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}


Vector PhyLabSimu::VecScale(Vector a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return a;
}

Vector PhyLabSimu::VecScale(double a, Vector b)
{
	b.x *= a;
	b.y *= a;
	b.z *= a;
	return b;
}

double PhyLabSimu::VecNorm(Vector a)
{
	double temp;
	temp = a.x * a.x + a.y * a.y + a.z * a.z;
	return sqrt(temp);
}

/*========================== PLBaseObject =============================*/
PLBaseObject::PLBaseObject()
{
	Mass = 0;
	ElectricQuantity = 0;
	strcpy_s(objName, "unnamed");
}

PLBaseObject::PLBaseObject(char _objName[], double _Mass, double _ElectricQuantity)
{
	Mass = _Mass;
	ElectricQuantity = _ElectricQuantity;
	strcpy_s(objName, _objName);
}

PLBaseObject::~PLBaseObject()
{
}

/*=========================== PLParticle ===============================*/
PLParticle::PLParticle()
{

}

PLParticle::~PLParticle()
{

}

/*=========================== PLRigidBody ==============================*/
PLRigidBody::PLRigidBody()
{
	InertialTensor = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
}

PLRigidBody::PLRigidBody(Tensor _IT)
{
	InertialTensor = _IT;
}

PLRigidBody::~PLRigidBody()
{
}

/*============================= PLBall =================================*/
PLBall::PLBall()
{
	Radius = 0;
}

PLBall::PLBall(double _Mass, double _Radius)
{
	Mass = _Mass;
	Radius = _Radius;
	double I = 0.4f * Mass * Radius * Radius;
	InertialTensor.xx = I;
	InertialTensor.xy = 0.0f;
	InertialTensor.xz = 0.0f;
	InertialTensor.yx = 0.0f;
	InertialTensor.yy = I;
	InertialTensor.yz = 0.0f;
	InertialTensor.zx = 0.0f;
	InertialTensor.zy = 0.0f;
	InertialTensor.zz = I;
}

PLBall::~PLBall()
{
}

/*============================= PLCube =================================*/
PLCube::PLCube()
{
	Lx = 0;
	Ly = 0;
	Lz = 0;
}

PLCube::PLCube(double _Lx, double _Ly, double _Lz)
{
	Lx = _Lx;
	Ly = _Ly;
	Lz = _Lz;
	InertialTensor.xx = Mass / 12.0f * (Ly * Ly + Lz * Lz);
	InertialTensor.xy = 0.0f;
	InertialTensor.xz = 0.0f;
	InertialTensor.yx = 0.0f;
	InertialTensor.yy = Mass / 12.0f * (Lx * Lx + Lz * Lz);
	InertialTensor.yz = 0.0f;
	InertialTensor.zx = 0.0f;
	InertialTensor.zy = 0.0f;
	InertialTensor.zz = Mass / 12.0f * (Lx * Lx + Ly * Ly);
}

PLCube::~PLCube()
{
}