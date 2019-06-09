#pragma once
#include <stdio.h>
#include <string.h>
#include <cmath>
namespace PhyLabSimu
{
	struct Vector
	{
		double x, y, z;
	};

	Vector VecAdd(Vector a, Vector b);
	Vector VecSub(Vector a, Vector b);
	double VecDot(Vector a, Vector b);
	Vector VecMul(Vector a, Vector b);
	Vector VecDiv(Vector a, Vector b);
	Vector VecScale(Vector a, double b);
	Vector VecScale(double a, Vector b);
	double VecNorm(Vector a);

	struct Tensor
	{
		double xx, xy, xz, yx, yy, yz, zx, zy, zz;
	};

	class PLBaseObject // Basic Class of all Objects.
	{
	public:
		PLBaseObject();
		PLBaseObject(char _objName[], double _Mass, double _ElectricQuantity);
		~PLBaseObject();

		char objName[32];
		double Mass;
		double ElectricQuantity;
	private:

	};

	class PLParticle : public PLBaseObject
	{
	public:
		PLParticle();
		~PLParticle();
	};

	class PLRigidBody : public PLBaseObject
	{
	public:
		PLRigidBody();
		PLRigidBody(Tensor _IT);
		~PLRigidBody();
		Tensor InertialTensor;
	private:

	};

	class PLBall : public PLRigidBody
	{
	public:
		PLBall();
		PLBall(double _Mass, double _Radius);
		~PLBall();
		double Radius;
	private:

	};

	class PLCube : public PLRigidBody
	{
	public:
		PLCube();
		PLCube(double _Lx, double _Ly, double _Lz);
		~PLCube();
		double Lx, Ly, Lz;
	private:

	};

	class PLWall : public PLBaseObject
	{
	public:
		PLWall(double _Width, double _Height);
		~PLWall();
		double Width, Height;
	private:

	};

}
