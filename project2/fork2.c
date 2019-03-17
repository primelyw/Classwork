//Copyright @ primelee;
//Source should be compiled on linux system.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/sem.h>
#include <stdlib.h>
#define NUM_LOOPS 50
#define ONE_SEC 999999999

void create_procs(int *);
void delta(struct sembuf*,int,int,int);
void delay_time(int);
void smoker(int);
void producer(int);

int sem_set_id;
struct sembuf sem_op;
char* m1[3] = {"tobacco","paper","glue"};


int main(){
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
    //running;
    switch(id){
        case 0: smoker(1);break;
        case 1: smoker(2);break;
        case 2: smoker(3);break;
        case 3: producer(1);break;
        case 4: producer(2); printf("\nDone!!!\n");break;
        default: return 0;break;
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

void smoker(int id){
    printf("\nSmoker%d: My pid is %d\n",id,getpid()); //sleep(1);
    for (int i=0; i<NUM_LOOPS; i++) {
        delta(&sem_op,id%3,sem_set_id,-1);
        delta(&sem_op,(id+1)%3,sem_set_id,-1);
        printf("\nSmoker%d: I get '%s' and '%s'. I can smoke for the %d times!!!\n",id,m1[id%3],m1[(id+1)%3],i+1);
        fflush(stdout);
    }
}

void producer(int id){
    int i = 0;
    printf("\nProducer%d: My pid is %d\n",id,getpid()); sleep(1);
    while(i<NUM_LOOPS*3){
        printf("\nProducer%d: '%s' is ready\n", id,m1[(i+id-1)%3]);
        fflush(stdout);
        delta(&sem_op,(i+id-1)%3,sem_set_id,+1);
        //sleep(2);
        delay_time(ONE_SEC/9);
        i+=1;
    }
}