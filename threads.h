/*CSE430 Project3 by Ruifeng Li and Ruihai Fang*/

#include "q.h"

void start_thread(void (*function)(void))
{ 
	TCB_t *tcb;
	char *stack_p;
	
	tcb=(TCB_t *)malloc(sizeof(TCB_t));
	stack_p=(char *)malloc(8192);

	init_TCB(tcb, function, stack_p, 8192);
	addQ(&head, tcb);
}

void run()
{
	ucontext_t initial_TCB;
	getcontext(&initial_TCB);
	swapcontext(&initial_TCB, &(head->context)); 
}

void yield()
{
    	TCB_t *prev;
	prev=head;
	rotateQ(&head);
	swapcontext(&(prev->context),&(head->context));
}
