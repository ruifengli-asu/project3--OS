/*CSE430 Project3 by Ruifeng Li and Ruihai Fang*/

#include "TCB.h"

typedef TCB_t node; 
TCB_t *head,*temp;


void initQ(TCB_t **q);
void addQ(TCB_t **q, TCB_t *context);
TCB_t* deleteQ(TCB_t **q);
void rotateQ(TCB_t **q);

void initQ(TCB_t **q)
{ 
	*q=NULL;
}


void addQ(TCB_t **q, TCB_t *new)
{
	if(*q==NULL)
	{
                *q = new;
		(*q)->next = new;
		(*q)->prev = new;
	}else
	{
                ((*q)->prev)->next = new;
         	new->prev = (*q)->prev;
		(*q)->prev = new;
		new->next = *q;
	}
	;
}


TCB_t* deleteQ(TCB_t **q)
{
 	if (*q == NULL)
	{
		 printf("There is no element in the queue \n");
		 exit(-1);
	}
	else if ((*q)-> next == *q)
	{
         	temp = *q;	
		*q = NULL;	
	}
	else
	{
		temp = *q;	
		((*q)->next)->prev = (*q)->prev;
		((*q)->prev)->next = (*q)->next;
		*q = (*q)->next;	
	}
	return temp;
}

/*Rotate the head pointer by one element*/
void rotateQ(TCB_t **q)
{
        if (*q == NULL)
	{ 
	         printf("No element in the queue, can not rotate \n");
        	 exit(-1);
	}
	
	addQ(q, deleteQ(q));//because deleteQ updates head and here the q will be old
}


