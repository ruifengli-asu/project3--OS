/*CSE430 Project3 by Ruifeng Li and Ruihai Fang*/

#include "threads.h"

typedef struct Semaphore 
{
	int value;
	TCB_t *waitQ;

} Semaphore;

Semaphore *createSem(int value)
{
	Semaphore *temp;
	temp = malloc(sizeof(Semaphore));

	initQ(&(temp->waitQ));
	temp->value = value;
	
	return temp;	
}

void P(Semaphore *sem)
{
	TCB_t *blockProcess = 0, *nextProcess = 0;
	sem->value--;
	if(sem->value < 0)
	{
		blockProcess = (TCB_t *)deleteQ(&head);
		addQ(&(sem->waitQ), blockProcess);
		nextProcess = head;
		swapcontext(&(blockProcess->context), &(nextProcess->context));
	}
}

void V(Semaphore *sem)
{
	TCB_t *unblockProcess;
	sem->value++;
	if(sem->value <=0)
	{
		unblockProcess = (TCB_t *)deleteQ(&(sem->waitQ));
		addQ(&head, unblockProcess);
	}
	yield();
}
