#include "Header Files/stdlib/mystdlib.h"

int main(void)
{
	printf("\n");
	matf4x4 s = matf4x4Default;

	s.matrix[0] = 3.0f;
	s.matrix[2] = 0.33f;
	s.matrix[5] = 5.0f;
	s.matrix[10] = 7.0f;
	s.matrix[9] = 5.5f;
	s.matrix[11] = 1.6f;
	s.matrix[15] = 2.0f;

	for (int row = 0; row < s.rows; row++)
	{
		printf(" ");
		for (int column = 0; column < s.columns; column++)
		{
			printf("%.0f ", s.matrix[(row * s.rows) + column]);
		}
		printf("\n");
	}

	printf("\n");

	matf4x4 ss = matf4x4Identity; 
	for (int row = 0; row < ss.rows; row++)
	{
		printf(" ");
		for (int column = 0; column < ss.columns; column++)
		{
			printf("%.0f ", ss.matrix[(row * ss.rows) + column]);
		}
		printf("\n");
	}
	printf("\n");

	matfSized matf = initMatfSized(6, 6);
	initMatfSizedIdentity(&matf);

	printf(" SizeMatRowsT : %d ;\n", matf.rows);
	printf(" SizeMatColumnsT : %d ;\n\n", matf.columns);

	for (unsigned char row = 0; row < matf.rows; row++)
	{
		printf(" ");
		for (unsigned char column = 0; column < matf.columns; column++)
		{
			printf("%.0f ", matf.matrix[(row * matf.columns) + column]);
		}
		printf("\n");
	}
	printf("\n");
	
	int top = 0;
	int testValue1 = 5;
	int testValue2 = 111;
	
	stack stackTest = initStack(10, sizeof(int));
	
	pushStack(&stackTest, &testValue1);
	pushStack(&stackTest, &testValue2);
	topStack(&stackTest, &top);

	printf(" Top : %d ;\n", top);

	popStack(&stackTest, &top);
	topStack(&stackTest, &top);

	printf(" Top : %d ;\n", top);

	freeStack(&stackTest);
	matfSizedFree(&matf);

	return 0;
}