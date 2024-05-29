#include "Header Files/stdlib/mystdlib.h"

int main(void)
{
	printf("\n");

	/* Start testing of matf functionality */
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
	/* End testing of matf functionality */

	/* Start testing of stack functionality */
	int top = 0;
	int testValue1 = 5;
	int testValue2 = 111;
	int testValue3 = 152;
	
	stack stackTest = initStack(10, sizeof(int));
	
	pushStack(&stackTest, &testValue1);
	pushStack(&stackTest, &testValue2);
	pushStack(&stackTest, &testValue3);
	peekStack(&stackTest, &top);

	printf(" Top : %d ;\n", top);
	popStack(&stackTest, &top);
	printf(" POP\n");
	peekStack(&stackTest, &top);
	printf(" Top : %d ;\n", top);
	popStack(&stackTest, &top);
	printf(" POP\n");
	peekStack(&stackTest, &top);
	printf(" Top : %d ;\n\n", top);
	/* End testing of stack functionality */

	/* Start testing of queue functionality */
	int next = 0;
	int testValue4 = 5;
	int testValue5 = 111;
	int testValue6 = 152;

	queue queueTest = initQueue(20, sizeof(int));

	enqueueQueue(&queueTest, &testValue4);
	enqueueQueue(&queueTest, &testValue5);
	enqueueQueue(&queueTest, &testValue6);
	peekQueue(&queueTest, &next);

	printf(" Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	printf(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	printf(" Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	printf(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	printf(" Next : %d ;\n\n", next);
	/* End testing of queue functionality */

	/* Start testing of memory freeing functionality */
	freeQueue(&queueTest);
	freeStack(&stackTest);
	matfSizedFree(&matf);
	/* End testing of memory freeing functionality */
	
	return 0;
}