#include "../../Header Files/stdlib/vector.h"

fvector3 fvec3(float x, float y, float z)
{
	fvector3 newVector3;
	newVector3.x = x;
	newVector3.y = y;
	newVector3.z = z;
	return newVector3;
}

fvector2 fvec2(float x, float y)
{
	fvector2 newVector2;
	newVector2.x = x;
	newVector2.y = y;
	return newVector2;
}

dvector3 dvec3(double x, double y, double z)
{
	dvector3 newdVector3;
	newdVector3.x = x;
	newdVector3.y = y;
	newdVector3.z = z;
	return newdVector3;
}

dvector2 dvec2(double x, double y)
{
	dvector2 newdVector2;
	newdVector2.x = x;
	newdVector2.y = y;
	return newdVector2;
}