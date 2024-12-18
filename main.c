#include "Header Files/stdlib/mystdlib.h"

int main(void)
{
	DebugPrint("\n");

	timer matrixTimer = TimerDefault;
	timer stackTimer = TimerDefault;
	timer queueTimer = TimerDefault;
	timer vectorTimer = TimerDefault;
	timer linkedListTimer = TimerDefault;
	timer hashTimer = TimerDefault;
	timer hashTableTimer = TimerDefault;
	timer arrayTimer = TimerDefault;
	timer memoryFreeTimer = TimerDefault;

	timerStart(&matrixTimer);
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
		DebugPrint(" ");
		for (int column = 0; column < s.columns; column++)
		{
			DebugPrint("%.0f ", s.matrix[(row * s.rows) + column]);
		}
		DebugPrint("\n");
	}
	DebugPrint("\n");

	matf4x4 ss = matf4x4Identity;
	for (int row = 0; row < ss.rows; row++)
	{
		DebugPrint(" ");
		for (int column = 0; column < ss.columns; column++)
		{
			DebugPrint("%.0f ", ss.matrix[(row * ss.rows) + column]);
		}
		DebugPrint("\n");
	}
	DebugPrint("\n");

	matfSized matf = initMatfSized(6, 6);
	initMatfSizedIdentity(&matf);

	DebugPrint(" SizeMatRowsT : %d ;\n", matf.rows);
	DebugPrint(" SizeMatColumnsT : %d ;\n\n", matf.columns);

	for (unsigned char row = 0; row < matf.rows; row++)
	{
		DebugPrint(" ");
		for (unsigned char column = 0; column < matf.columns; column++)
		{
			DebugPrint("%.0f ", matf.matrix[(row * matf.columns) + column]);
		}
		DebugPrint("\n");
	}
	/* End testing of matf functionality */
	timerStop(&matrixTimer);
	timerPrintDelta(matrixTimer, "MatrixTests: ");

	timerStart(&stackTimer);
	/* Start testing of stack functionality */
	int top = 0;
	int testValue1 = 5;
	int testValue2 = 11100;
	int testValue3 = 152;

	stack stackTest = initStack(10, sizeof(int));

	pushStack(&stackTest, &testValue1);
	pushStack(&stackTest, &testValue2);
	pushStack(&stackTest, &testValue3);
	peekStack(&stackTest, &top);

	DebugPrint("\n Top : %d ;\n", top);
	popStack(&stackTest, &top);
	DebugPrint(" POP\n");
	peekStack(&stackTest, &top);
	DebugPrint(" Top : %d ;\n", top);
	popStack(&stackTest, &top);
	DebugPrint(" POP\n");
	peekStack(&stackTest, &top);
	DebugPrint(" Top : %d ;\n", top);
	/* End testing of stack functionality */
	timerStop(&stackTimer);
	timerPrintDelta(stackTimer, "StackTests: ");

	timerStart(&queueTimer);
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

	DebugPrint("\n Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	DebugPrint(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	DebugPrint(" Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	DebugPrint(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	DebugPrint(" Next : %d ;\n", next);
	/* End testing of queue functionality */
	timerStop(&queueTimer);
	timerPrintDelta(queueTimer, "QueueTests: ");

	timerStart(&vectorTimer);
	/* Start testing of vector functionality */
	fvector3 testVec1 = fvec3(0.0f, 0.0f, 0.0f);
	fvector2 testVec2 = fvec2(0.0f, 0.0f);
	dvector3 testVec3 = dvec3(0.0, 0.0, 0.0);
	dvector2 testVec4 = dvec2(0.0, 0.0);

	DebugPrint("\n testVec1 : x{%.1f}, y{%.1f}, z{%.1f} ;\n", testVec1.x, testVec1.y, testVec1.z);
	DebugPrint(" testVec2 : x{%.1f}, y{%.1f} ;\n", testVec2.x, testVec2.y);
	DebugPrint(" testVec3 : x{%.1f}, y{%.1f}, z{%.1f} ;\n", testVec3.x, testVec3.y, testVec3.z);
	DebugPrint(" testVec4 : x{%.1f}, y{%.1f} ;\n", testVec4.x, testVec4.y);
	/* End testing of vector functionality */
	timerStop(&vectorTimer);
	timerPrintDelta(vectorTimer, "VectorTests: ");

	timerStart(&linkedListTimer);
	/* Start testing of linkedList functionality */
	linkedList testLinkedList = initLinkedList();

	float testFloatValue1 = 12.5f;
	node testNode1 = initLinkedListNode(&testFloatValue1);
	insertIntoLinkedListBeginning(&testLinkedList, testNode1);

	unsigned int testIntValue1 = 11;
	node testNode2 = initLinkedListNode(&testIntValue1);
	insertIntoLinkedListBeginning(&testLinkedList, testNode2);

	double testDoubleValue1 = 15.7;
	node testNode3 = initLinkedListNode(&testDoubleValue1);
	insertIntoLinkedListBeginning(&testLinkedList, testNode3);

	DebugPrint("\n New next value of node2 :: %.3f ;\n", *(float*)testNode2->next->value);
	DebugPrint(" New previous value of node1 :: %d ;\n", *(int*)testNode1->previous->value);
    DebugPrint(" New head of linkedList :: %.6f ;\n", *(double*)testLinkedList->head->value);
    DebugPrint(" New tail of linkedList :: %.3f ;\n", *(float*)testLinkedList->tail->value);
	/* End testing of linkedList functionality */
	timerStop(&linkedListTimer);
	timerPrintDelta(linkedListTimer, "LinkedListTests: ");

	timerStart(&hashTimer);
	/* Start testing of hash functionality */
	unsigned int max = 4294967290;
	DebugPrint("\n UINT_MAX_BYTE0 :: %d ;\n", max % 255);

	unsigned int key = 2222;
	unsigned int outHash = murmur32Hash(&key, sizeof(key), 0);
	DebugPrint(" KEY {2222} HASHOUT :: %u | %x ;\n", outHash, outHash);

	unsigned int key2 = 4323;
	unsigned int outHash2 = fnv1AHash(&key2, sizeof(key2), 0);
	DebugPrint(" KEY2 {4323} HASHOUT :: %u | %x ;\n", outHash2, outHash2);
	/* End testing of hash functionality */
	timerStop(&hashTimer);
	timerPrintDelta(hashTimer, "HashingTests: ");

	timerStart(&hashTableTimer);
	/* Start testing of hashTable functionality */
	hashTable testHashTable1 = initHashTable(UnsignedIntEqual, 4, 8, 1, 1024);

	int testHashTableKey1 = 2;
	double testHashTableValue1 = 2312.22;
	insertIntoHashTable(testHashTable1, 
						&testHashTableKey1, &testHashTableValue1);

	int testHashTableKey2 = 2;
	double testHashTableValue2 = 231231.2;
	insertIntoHashTable(testHashTable1,
						&testHashTableKey2, &testHashTableValue2);

	keyPair testHashTableKeyPair1 = searchHashTable(testHashTable1, &testHashTableKey1);

	DebugPrint("Key1 :: %d ; Value1 :: %.3f ;\n", *(int*)testHashTableKeyPair1->key, *(double*)testHashTableKeyPair1->value);

	int idx = 0;
	while (idx < testHashTable1->capacity)
	{
		int someTestKey1 = idx;
		double someTestValue1 = 1.0 * someTestKey1;

		insertIntoHashTable(testHashTable1,
							&someTestKey1, &someTestValue1);
		idx += 1;
	}
	/* End testing of hashTable functionality */
	timerStop(&hashTableTimer);
	timerPrintDelta(hashTableTimer, "hashTableTests: ");

	timerStart(&arrayTimer);
	/* Start testing of dArray functionality */
	tArray testArray1 = initArray(100, sizeof(int));

	int testItem1 = 123;
	pushArray(&testArray1, &testItem1);

	int outputTest1 = 0;
	getArrayAtIndex(&testArray1, &outputTest1, 0);

	DebugPrint("\n Item at idx[0] :: %d ;\n", outputTest1);
	/* End testing of dArray functionality */
	timerStop(&arrayTimer);
	timerPrintDelta(arrayTimer, "DynamicArrayTests: ");

	timerStart(&memoryFreeTimer);
	/* Start testing of memory freeing functionality */
	matfSizedFree(&matf);
	freeStack(&stackTest);
	freeQueue(&queueTest);
	freeLinkedList(&testLinkedList);
	//freeChainedhashTable(&testchainedhashTable1);
	freeHashTable(testHashTable1);
	freeKeyPair(testHashTableKeyPair1);
	freeArray(&testArray1);
	/* End testing of memory freeing functionality */
	timerStop(&memoryFreeTimer);
	timerPrintDelta(memoryFreeTimer, "FreeMemoryTests: ");

	double totalDeltaInSeconds = timerDelta(&matrixTimer) + timerDelta(&stackTimer) + timerDelta(&queueTimer) + timerDelta(&vectorTimer) + timerDelta(&linkedListTimer) + timerDelta(&hashTimer) + timerDelta(&arrayTimer) + timerDelta(&hashTableTimer) + timerDelta(&memoryFreeTimer);
	printf("\ntotalDelta: %.16f seconds . . .\n", totalDeltaInSeconds);
	printf("\n");

	return 0;
}
