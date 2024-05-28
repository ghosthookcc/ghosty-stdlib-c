#include "../../Header Files/stdlib/matrix.h"

matfSized initMatfSized(unsigned char rows, unsigned char columns)
{
	matfSized newMatf;
	newMatf.rows = rows;
	newMatf.columns = columns;
	newMatf.matrix = calloc((rows * columns), sizeof(float));
	return newMatf;
} 

void initMatfSizedIdentity(matfSized* matf)
{
	if (matf->rows == matf->columns && matf->rows > 1)
	{
		unsigned char jumpedRows = 0;
		for (unsigned char row = 0; row < matf->rows; row++)
		{
			matf->matrix[(jumpedRows * matf->columns) + jumpedRows] = 1.0f;
			jumpedRows++; 
		}
	}
}

void matfSizedFree(matfSized* matf)
{
	free(matf->matrix);
}