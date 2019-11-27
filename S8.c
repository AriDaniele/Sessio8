//*************************************************************
//Sistemes Operatius. Sessió 8            
//Clara Valls - clara.valls                   
//Ariel Andreas Daniele - arielandreas.daniele

//Llibreries
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "semaphore_v2.h"

semaphore *sem;
static int glob = 0;

static void * threadFunc (void *arg)
{
	int loops = *((int *) arg);
	int j;

	for (j = 0; j < loops; j++){
		SEM_wait(sem);
		glob++;
		SEM_signal(sem);
	}
	return NULL;
}


int main(void){
    pthread_t t1, t2;
    int loops, s;

    sem = (semaphore *) malloc(sizeof(semaphore));
    
	SEM_constructor(sem);
	SEM_init(sem, 1);

    s = pthread_create (&t1, NULL, threadFunc, &loops);
	s = pthread_create (&t2, NULL, threadFunc, &loops);

	s = pthread_join (t1, NULL);
	s = pthread_join (t2, NULL);

    SEM_destructor(sem);
}

/**
 * CREAR MEMÒRIA COMPARTIDA
    int main(){
        int memid;
        int *num;
        memid=shmget(0xCAFECAFE,sizeof(int),IPC_CREAT|IPC_EXCL|0600);
        
        if (memid>0){
            num=shmat(memid,0,0);
            *num=0;
            
            while(*num!=-1){
                printf("Numero:");
                scanf("%d",num);
            }

            shmdt(num);
            shmctl (memid, IPC_RMID, NULL );
        }
        else{
            printf ("Regió ja existent\n");
        }
        return 0;
    }
*/