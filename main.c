#include "Header Files/stdlib/hash.h"
#include "Header Files/stdlib/hashtable.h"
#include "Header Files/stdlib/linkedList.h"
#include "Header Files/stdlib/mystdlib.h"

int main(void)
{
	//printf("\n");

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
		//printf(" ");
		for (int column = 0; column < s.columns; column++)
		{
			//printf("%.0f ", s.matrix[(row * s.rows) + column]);
		}
		//printf("\n");
	}

	//printf("\n");

	matf4x4 ss = matf4x4Identity;
	for (int row = 0; row < ss.rows; row++)
	{
		//printf(" ");
		for (int column = 0; column < ss.columns; column++)
		{
			//printf("%.0f ", ss.matrix[(row * ss.rows) + column]);
		}
		//printf("\n");
	}
	//printf("\n");

	matfSized matf = initMatfSized(6, 6);
	initMatfSizedIdentity(&matf);

	//printf(" SizeMatRowsT : %d ;\n", matf.rows);
	//printf(" SizeMatColumnsT : %d ;\n\n", matf.columns);

	for (unsigned char row = 0; row < matf.rows; row++)
	{
		//printf(" ");
		for (unsigned char column = 0; column < matf.columns; column++)
		{
			//printf("%.0f ", matf.matrix[(row * matf.columns) + column]);
		}
		//printf("\n");
	}
	//printf("\n");
	/* End testing of matf functionality */
	timerStop(&matrixTimer);
	timerPrintDelta(matrixTimer);

	unsigned int testKey = 11;
	float testValue = 123.124f;
	keyPair test = initKeyPair(&testKey, &testValue, 4, UnsignedIntEqual);

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

	//printf(" Top : %d ;\n", top);
	popStack(&stackTest, &top);
	//printf(" POP\n");
	peekStack(&stackTest, &top);
	//printf(" Top : %d ;\n", top);
	popStack(&stackTest, &top);
	//printf(" POP\n");
	peekStack(&stackTest, &top);
	//printf(" Top : %d ;\n\n", top);
	/* End testing of stack functionality */
	timerStop(&stackTimer);
	timerPrintDelta(stackTimer);

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

	//printf(" Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	//printf(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	//printf(" Next : %d ;\n", next);
	dequeueQueue(&queueTest, &next);
	//printf(" DEQUEUE\n");
	peekQueue(&queueTest, &next);
	//printf(" Next : %d ;\n\n", next);
	/* End testing of queue functionality */
	timerStop(&queueTimer);
	timerPrintDelta(queueTimer);

	timerStart(&vectorTimer);
	/* Start testing of vector functionality */
	fvector3 testVec1 = fvec3(0.0f, 0.0f, 0.0f);
	fvector2 testVec2 = fvec2(0.0f, 0.0f);
	dvector3 testVec3 = dvec3(0.0, 0.0, 0.0);
	dvector2 testVec4 = dvec2(0.0, 0.0);

	//printf(" testVec1 : x{%.1f}, y{%.1f}, z{%.1f} ;\n", testVec1.x, testVec1.y, testVec1.z);
	//printf(" testVec2 : x{%.1f}, y{%.1f} ;\n", testVec2.x, testVec2.y);
	//printf(" testVec3 : x{%.1f}, y{%.1f}, z{%.1f} ;\n", testVec3.x, testVec3.y, testVec3.z);
	//printf(" testVec4 : x{%.1f}, y{%.1f} ;\n\n", testVec4.x, testVec4.y);
	/* End testing of vector functionality */
	timerStop(&vectorTimer);
	timerPrintDelta(vectorTimer);

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

	//printf(" New next value of node2 :: %.3f ;\n", *(float*)testNode2->next->value);
	//printf(" New previous value of node1 :: %d ;\n", *(int*)testNode1->previous->value);
    //printf(" New head of linkedList :: %.6f ;\n", *(double*)testLinkedList->head->value);
    //printf(" New tail of linkedList :: %.3f ;\n\n", *(float*)testLinkedList->tail->value);
	/* End testing of linkedList functionality */
	timerStop(&linkedListTimer);
	timerPrintDelta(linkedListTimer);

	timerStart(&hashTimer);
	/* Start testing of hash functionality */
	unsigned int UINT_MAX = 4294967290;
	//printf(" UINT_MAX_BYTE0 :: %d ;\n", UINT_MAX % 0b11111111);

	unsigned int key = 2222;
	unsigned int outHash = murmur32Hash(&key, sizeof(key), 0);
	//printf(" KEY {2222} HASHOUT :: %u | %x ;\n", outHash, outHash);

	unsigned int key2 = 4323;
	unsigned int outHash2 = fnv1AHash(&key2, sizeof(key2), 0);
	//printf(" KEY2 {4323} HASHOUT :: %u | %x ;", outHash2, outHash2);
	//printf("\n\n");
	/* End testing of hash functionality */
	timerStop(&hashTimer);
	timerPrintDelta(hashTimer);

	timerStart(&hashTableTimer);
	/* Start testing of hashtable functionality */
	chainedHashTable testchainedHashTable1 = initChainedHashTable(100);

	unsigned int keyName1 = 12;
	float keyValue1 = 53.2f;
	keyPair testKeyPair1 = insertIntoChainedHashTable(&testchainedHashTable1, &keyName1, &keyValue1, 4, UnsignedIntEqual);
	printf("\nTestInsert1ValueKey :: %u ;\n", VOIDPTR_CAST(unsigned int, testKeyPair1->key));

	unsigned int keyName2 = 12;
	int keyValue2 = 4;
	keyPair testKeyPair2 = insertIntoChainedHashTable(&testchainedHashTable1, &keyName2, &keyValue2, 4, UnsignedIntEqual);
	printf("TestInsert2ValueKey :: %u ;\n", VOIDPTR_CAST(unsigned int, testKeyPair2->key));

	unsigned int keyName3 = 1231;
	float keyValue3 = 12312.223f;
	keyPair testKeyPair3 = insertIntoChainedHashTable(&testchainedHashTable1, &keyName3, &keyValue3, 4, UnsignedIntEqual);
	printf("TestInsert3ValueKey :: %u ;\n\n", VOIDPTR_CAST(unsigned int, testKeyPair3->key));

	keyPair testSearch1 = searchChainedHashTable(testchainedHashTable1, testKeyPair1);
	printf("TestSearch1Value :: %d ;\n", VOIDPTR_CAST(int, testSearch1->value));
	keyPair testSearch2 = searchChainedHashTable(testchainedHashTable1, testKeyPair2);
	printf("TestSearch2Value :: %d ;\n", VOIDPTR_CAST(int, testSearch2->value));
	keyPair testSearch3 = searchChainedHashTable(testchainedHashTable1, testKeyPair3);
	printf("TestSearch3Value :: %.2f ;\n\n\n", VOIDPTR_CAST(float, testSearch3->value));
	
	openHashTable testopenHashTable1 = initOpenHashTable(100);

	unsigned int openKeyName1 = 12;
	float openKeyValue1 = 2131.23f;
	keyPair testOpenKeyPair1 = insertIntoOpenHashTable(&testopenHashTable1, &openKeyName1, &openKeyValue1, 4, UnsignedIntEqual);
	printf("TestOpenInsert1 :: %u ;\n", VOIDPTR_CAST(unsigned int, testOpenKeyPair1->key));

	unsigned int openKeyName2 = 12;
	int openKeyValue2 = 541;
	keyPair testOpenKeyPair2 = insertIntoOpenHashTable(&testopenHashTable1, &openKeyName2, &openKeyValue2, 4, UnsignedIntEqual);
	printf("TestOpenInsert2 :: %u ;\n", VOIDPTR_CAST(unsigned int, testOpenKeyPair2->key));

	unsigned int openKeyName3 = 1231;
	float openKeyValue3 = 4123521.23f;
	keyPair testOpenKeyPair3 = insertIntoOpenHashTable(&testopenHashTable1, &openKeyName3, &openKeyValue3, 4, UnsignedIntEqual);
	printf("TestOpenInsert3 :: %u ;\n\n", VOIDPTR_CAST(unsigned int, testOpenKeyPair3->key));

	keyPair testOpenSearch1 = searchOpenHashTable(testopenHashTable1, testOpenKeyPair1);
	printf("TestOpenSearch1Value :: %d ;\n", VOIDPTR_CAST(int, testOpenSearch1->value));
	keyPair testOpenSearch2 = searchOpenHashTable(testopenHashTable1, testOpenKeyPair2);
	printf("TestOpenSearch2Value :: %d ;\n", VOIDPTR_CAST(int, testOpenSearch2->value));
	keyPair testOpenSearch3 = searchOpenHashTable(testopenHashTable1, testOpenKeyPair3);
	printf("TestOpenSearch3Value :: %.2f ;\n", VOIDPTR_CAST(float, testOpenSearch3->value));
	/* End testing of hashtable functionality */
	timerStop(&hashTableTimer);
	timerPrintDelta(hashTableTimer);

	timerStart(&arrayTimer);
	/* Start testing of dArray functionality */
	tArray testArray1 = initArray(100, sizeof(int));

	int testItem1 = 123;
	pushArray(&testArray1, &testItem1);

	int outputTest1 = 0;
	getArrayAtIndex(&testArray1, &outputTest1, 0);

	printf("\nItem at idx[0] :: %d ;\n", outputTest1);

	/* End testing of dArray functionality */
	timerStop(&arrayTimer);
	timerPrintDelta(arrayTimer);

	timerStart(&memoryFreeTimer);
	/* Start testing of memory freeing functionality */
	matfSizedFree(&matf);
	freeStack(&stackTest);
	freeQueue(&queueTest);
	freeLinkedList(&testLinkedList);
	freeChainedHashTable(&testchainedHashTable1);
	freeOpenHashTable(&testopenHashTable1);
	freeArray(&testArray1);
	free(test);
	/* End testing of memory freeing functionality */
	timerStop(&memoryFreeTimer);
	timerPrintDelta(memoryFreeTimer);

	double totalDeltaInSeconds = timerDelta(&matrixTimer) + timerDelta(&stackTimer) + timerDelta(&queueTimer) + timerDelta(&vectorTimer) + timerDelta(&linkedListTimer) + timerDelta(&hashTimer) + timerDelta(&arrayTimer) + timerDelta(&hashTableTimer) + timerDelta(&memoryFreeTimer);
	printf("\ntotalDelta: %.16f seconds . . .\n", totalDeltaInSeconds);
	printf("\n");

	return 0;
}
