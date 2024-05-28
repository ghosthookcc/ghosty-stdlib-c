#ifndef MATRIX_H
#define MATRIX_H

/* Start matrix 4 size */

typedef struct matf4x4_t
{
	float matrix[16];
	unsigned char rows;
	unsigned char columns;
} matf4x4;
static const matf4x4 matf4x4Default =
{
	.matrix = { 0, 0, 0, 0, 
				0, 0, 0, 0, 
				0, 0, 0, 0, 
				0, 0, 0, 0 },
	.rows = 4, .columns = 4
};
static const matf4x4 matf4x4Identity = 
{
	.matrix = { 1, 0, 0, 0, 
				0, 1, 0, 0, 
				0, 0, 1, 0, 
				0, 0, 0, 1 },
	.rows = 4, .columns = 4
};

struct matf4x3_b
{
	float matrix[12];
	unsigned char rows;
	unsigned char columns;
};
typedef struct matf4x3_b matf4x3;
static const matf4x3 matf4x3Default = 
{
	.matrix = { 0, 0, 0, 
				0, 0, 0, 
				0, 0, 0, 
				0, 0, 0 },
	.rows = 4, .columns = 3	
};
typedef struct matf4x3_b matf3x4;
static const matf3x4 matf3x4Default =
{
	.matrix = { 0, 0, 0, 0, 
			    0, 0, 0, 0, 
			    0, 0, 0, 0 },
	.rows = 3, .columns = 4
};

struct matf4x2_b 
{
	float matrix[8];
	unsigned char rows;
	unsigned char columns;
};
typedef struct matf4x2_b matf4x2;
static const matf4x2 matf4x2Default =
{
	.matrix = { 0, 0, 
				0, 0, 
				0, 0, 
				0, 0 },
	.rows = 4, .columns = 2
};
typedef struct matf4x2_b matf2x4;
static const matf2x4 matf2x4Default =
{
	.matrix = { 0, 0, 0, 0, 
			    0, 0, 0, 0 },
	.rows = 2, .columns = 4
};

struct matf4x1_b 
{
    float matrix[4];
	unsigned int rows;
	unsigned int columns;
};
typedef struct matf4x1_b matf4x1;
static const matf4x1 matf4x1Default =
{
	.matrix = { 0, 
				0, 
				0, 
				0 },
	.rows = 4, .columns = 1
};
typedef struct matf4x1_b matf1x4;
static const matf1x4 matf1x4Default = 
{
	.matrix = { 0, 0, 0, 0 },
	.rows = 1, .columns = 4
};

/* End matrix 4 size */

/* Start matrix 3 size */

typedef struct matf3x3_t
{
	float matrix[9];
	unsigned char rows;
	unsigned char columns;
} matf3x3;
static const matf3x3 matf3x3Default =
{
	.matrix = { 0, 0, 0, 
				0, 0, 0, 
				0, 0, 0 },
	.rows = 3, .columns = 3
};
static const matf3x3 matf3x3Identity =
{
	.matrix = { 1, 0, 0, 
				0, 1, 0, 
				0, 0, 1 },
	.rows = 3, .columns = 3	
};

struct matf3x2_b
{
	float matrix[6];
	unsigned char rows;
	unsigned char columns;
};
typedef struct matf3x2_b matf3x2;
static const matf3x2 matf3x2Default = 
{
	.matrix = { 0, 0, 
				0, 0, 
				0, 0 },
	.rows = 3, .columns = 2	
};
typedef struct matf3x2_b matf2x3;
static const matf2x3 matf2x3Default =
{
	.matrix = { 0, 0, 0, 
				0, 0, 0 },
	.rows = 2, .columns = 3
};

struct matf3x1_b
{
	float matrix[3];
	unsigned char rows;
	unsigned char columns;
};
typedef struct matf3x1_b matf3x1;
static const matf3x1 matf3x1Default =
{
	.matrix = { 0, 
				0, 
				0 },
	.rows = 3, .columns = 1
};
typedef struct matf3x1_b matf1x3;
static const matf1x3 matf1x3Default = 
{
	.matrix = { 0, 0, 0 },
	.rows = 1, .columns = 3
};

/* End matrix 3 size */

/* Start matrix 2 size */

typedef struct matf2x2_t
{
	float matrix[4];
	unsigned char rows;
	unsigned char columns;
} matf2x2;
static const matf2x2 matf2x2Default =
{
	.matrix = { 0, 0, 
				0, 0 },
	.rows = 2, .columns = 2
};
static const matf2x2 matf2x2Identity =
{
	.matrix = { 1, 0, 
				0, 1 },
	.rows = 2, .columns = 2
};

struct matf2x1_b
{
	float matrix[2];
	unsigned char rows;
	unsigned char columns;
};
typedef struct matf2x1_b matf2x1;
static const matf2x1 matf2x1Default =
{
	.matrix = { 0, 
				0 },
	.rows = 2, .columns = 1
};
typedef struct matf2x1_b matf1x2;
static const matf1x2 matf1x2Default = 
{
	.matrix = { 0, 0 },
	.rows = 1, .columns = 2
};

/* End matrix 2 size */

#endif