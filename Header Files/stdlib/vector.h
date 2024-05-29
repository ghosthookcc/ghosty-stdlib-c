#ifndef VECTOR_H
#define VECTOR_H

typedef struct fvector3_t
{
	float x;
	float y;
	float z;
} fvector3;

typedef struct fvector2_t
{
	float x;
	float y;
} fvector2;

typedef struct dvector3_t
{
	double x;
	double y;
	double z;
} dvector3;

typedef struct dvector2_t
{
	double x;
	double y;
} dvector2;

fvector3 fvec3(float x, float y, float z);
fvector2 fvec2(float x, float y);
dvector3 dvec3(double x, double y, double z);
dvector2 dvec2(double x, double y);

#endif