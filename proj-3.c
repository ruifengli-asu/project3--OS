/*CSE430 Project3 by Ruifeng Li and Ruihai Fang*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

Semaphore *r_sem, *w_sem, *mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID=0;

void reader_entry(int ID)
{
	printf("[reader: #%d]\tpreparing to read\n", ID);
	P(mutex);
	if (wwc > 0 || wc > 0) {
	    printf("[reader: #%d]\tblocking for writer\n", ID);
	    rwc++;		
	    V(mutex);		
	    P(r_sem);	
	    rwc--;	
			// get into Critical Section.
	}
	rc++;
	if (rwc > 0)
	    V(r_sem);
	else
	    V(mutex);		// release the mutex.
}

void reader_exit(int ID)
{
	P(mutex);
	rc--;	
	if (rc == 0 && wwc > 0) {
	    
	    V(w_sem);
	} else
	    V(mutex);

}

void writer_entry(int ID)
{
	printf("\t\t\t\t[writer: #%d]\tpreparing to write\n", ID);
	P(mutex);
	if (rc > 0 || wc > 0) {
	    printf("\t\t\t\t[writer: #%d] blocking for others\n",ID);
	    wwc++;		
	    V(mutex);		
	    P(w_sem);		
	    wwc--;		
	}
	wc++;			
	V(mutex);		
}

void writer_exit(int ID)
{
	P(mutex);
	wc--;
	if (rwc > 0) {		
	    V(r_sem);
	} else if (wwc > 0) {	
	    V(w_sem);
	} else {		
	    V(mutex);
	}
}

void reader(void)
{ 
  int ID;
  P(mutex); ID = global_ID++; V(mutex);
  while(1){
	reader_entry(ID);
	printf("[reader #%d]\t****READING****\n", ID);
	sleep(1);
	reader_exit(ID);
  };
}

void writer(void)
{
  int ID;
  P(mutex); ID = global_ID++; V(mutex);
  while(1){
 	writer_entry(ID);
	printf("\t\t\t\t[writer: #%d]\t&&&WRITING!&&&\n", ID);
	sleep(1);
	writer_exit(ID);
  };
}

int main()
{
    mutex = createSem(1);
    r_sem = createSem(0);
    w_sem = createSem(0);

    start_thread(reader);
    start_thread(reader);
    start_thread(reader);
    start_thread(reader);
    start_thread(writer);
    start_thread(writer);

    run();
}   




