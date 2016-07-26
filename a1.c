/*Chase Cabrera masc1074
Michael Potts masc####
June 5th, 2015
Professor Leonard
CS570 Summer 2015
Assignment 1
a1.c
*/


#include "a1.h"
static sem_t LOCK;

void initSemaphores(void) {
	CHK(sem_init(&LOCK,LOCAL,1));        /*initialize the semaphore using CHK.h*/
 }
FILE *fp;

void * write_threadid(void *thr){ /*threads id written to SHARED.txt*/
		int i, id;
		id = (int) thr;
		for(i=0; i<10; i++){
			sem_wait(&LOCK);
			fopen("SHARED.txt", "a+");   /*a+ used to check if the file exists already and then to append it*/
			fprintf(fp, "thread id: < %d > \n", id );
			printf("Thread <%d> is running.\n", id);
			
			sem_post(&LOCK);			
			sleep(1);   /*avoids the race for stdout*/
		}
		fclose(fp);		/*close the file*/
		pthread_exit((void *) thr);	/*exit individual thread*/
		
}
	


int main(int argc, char *argv[]) {    /*first thread*/
	
	fp = fopen("SHARED.txt", "w");	/*first open and creation of SHARED.txt*/
	
	static pthread_t threads[MAXNUMBER];  /*declaring the threads*/
	pid_t pid;
	int thr, r;
	pid=fork();    /*fork a new process*/
	sem_wait(&LOCK);
	fprintf(fp, "child process id: < %lu > \n", pid );	/*fprintf used to write to an external file*/
	sem_post(&LOCK);
	fclose(fp);
	if (pid==0){ /*now in the child process*/
		for(thr = 0; thr<10; thr++){		/*create 10 threads and send the threads to writethread()*/
			r = pthread_create(&threads[thr], NULL, write_threadid, (void *)thr);
			if (r){	/*the thread creation failed*/
				printf("error: could not create thread <%d> \n", r);
				exit(1);     /*return of 1 indicates failure*/
			}
		}
		pthread_exit(NULL); /*all threads finished*/
		sem_destroy(&LOCK); /*destroy our Semaphore*/
		fclose(fp);		/*close the open file*/
		exit(0);  /*success!!!*/
		
	}
	else if(pid < 0){
		printf("error: fork failed, no more memory to create child process.");
	}
	else{
		freopen("SHARED.txt", "a+", fp);  /*file was closed earlier so we reopen it to write the parent process id*/
		sem_wait(&LOCK);
		fprintf(fp, "process id: < %lu > \n", getpid() );
		sem_post(&LOCK);
		wait(NULL);
		exit(0);
			
	}
	exit(0);
}

	
