//Copyright @ primelee;
//Source should be compiled on linux system.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/sem.h>
#include <stdlib.h>
#define NUM_LOOPS 1
#define ONE_SEC 999999999
char* m1[3] = {"tobacco","paper","glue"};
void create_procs(int *);
void delta(struct sembuf*,int,int,int);
void delay_time(int);

union semun {
        int val;                    /* value for SETVAL */
        struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
        unsigned short int *array;  /* array for GETALL, SETALL */
        struct seminfo *__buf;      /* buffer for IPC_INFO */
};


int main(){
    int sem_set_id;
    union semun sem_val; 
    struct sembuf sem_op;
    struct timespec delay;

    //create semaphore;
    sem_set_id = semget(IPC_PRIVATE, 3, 0600);
    if (sem_set_id == -1) {
        perror("main: semget");
        return 0;
    }
    for(int i = 0; i<3; i++) semctl(sem_set_id, i, SETVAL, 0);

    //create procs;
    int id;
    create_procs(&id);
    int i; //loop counter;
    switch(id){
        case 0:
            printf("\nSmoker1: My pid is %d\n",getpid()); //sleep(1);
            for (i=0; i<NUM_LOOPS; i++) {
                delta(&sem_op,1,sem_set_id,-1);
                delta(&sem_op,2,sem_set_id,-1);
                printf("\nSmoker1: I get 'paper' and 'glue'. I can smoke!!!\n");
                fflush(stdout);
            }
            break;
        case 1: 
            printf("\nSmoker2: My pid is %d\n",getpid()); //sleep(1);
            for (i=0; i<NUM_LOOPS; i++) {
                delta(&sem_op,0,sem_set_id,-1);
                delta(&sem_op,2,sem_set_id,-1);
                printf("\nSmoker2: I get 'tobacco' and 'glue'. I can smoke!!!\n");
                fflush(stdout);
            }
            break;
        case 2:
            printf("\nSmoker3: My pid is %d\n",getpid()); //sleep(1);
            for (i=0; i<NUM_LOOPS; i++) {
                delta(&sem_op,0,sem_set_id,-1);
                delta(&sem_op,1,sem_set_id,-1);
                printf("\nSmoker3: I get 'tobacco' and 'papper'. I can smoke!!!\n");
                fflush(stdout);
            }
            break;
        case 3:
            i = 0;
            printf("\nProducer1: My pid is %d\n",getpid()); sleep(1);
            while(i<NUM_LOOPS*3){
                printf("\nProducer1: '%s' is ready\n", m1[i%3]);
                fflush(stdout);
                delta(&sem_op,i%3,sem_set_id,+1);
                //sleep(1);
                delay_time(ONE_SEC/3);
                i+=1;
	        }
            break;
        case 4:
            i = 0;
            printf("\nProducer2: My pid is %d\n",getpid()); sleep(1);
            while(i<NUM_LOOPS*3){
                printf("\nProducer2: '%s' is ready\n", m1[(i+1)%3]);
                fflush(stdout);
                delta(&sem_op,(i+1)%3,sem_set_id,+1);
                //sleep(1);
                delay_time(ONE_SEC/3);
                i+=1;
	        }
            printf("Done\n");
            break;
        default:
            return 0;
            break;
    }
    
    return 0;
}

void create_procs(int *id){
    int p1,p2,p3;
    p1 = fork();
    p2 = fork();
    p3 = fork();
    if(p1!=0) p1 = 1;
    if(p2!=0) p2 = 1;
    if(p3!=0) p3 = 1;
    *id = p1+p2*2+p3*4;
}

void delta(struct sembuf* sem_op,int num,int sem_set_id,int increase){
    sem_op->sem_num = num;
    sem_op->sem_op = increase;
    sem_op->sem_flg = 0;
    semop(sem_set_id, sem_op, 1);
}

void delay_time(int nanosec){
     struct timespec delay;
     delay.tv_nsec = nanosec;
     delay.tv_sec = 0;
     nanosleep(&delay,NULL);
}