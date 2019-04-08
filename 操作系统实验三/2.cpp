#include<fcntl.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include <sched.h>

int ticketCount = 1000;
int temp;
sem_t *empty = NULL;
sem_t *full = NULL;
void pthread_yield();

void *worker1(void *arg){//售票进程
	for (int i = 0; i<30; i++){
		sem_wait(empty);
		//售票进程关键代码
		temp = ticketCount;
		pthread_yield();
		temp = temp - 1;
		pthread_yield();
		ticketCount = temp;
		printf("after the Sell,the number of ticketCount is :%d\n", ticketCount);
		sem_post(full);
	}
}
void *worker2(void *arg){//退票进程
	for (int i = 0; i<10; i++){
		sem_wait(full);
		//退票进程关键代码
		temp = ticketCount;
		pthread_yield();
		temp = temp + 1;
		pthread_yield();
		ticketCount = temp;
		printf("after the back,the number of ticketCount is :%d\n", ticketCount);
		sem_post(empty);
	}
}
int main(int argc, char *argv[]){
	pthread_t p1, p2;//创建两个进程
	empty = sem_open("emptyName", O_CREAT, 0666, 1000);//票数是否为空
	full = sem_open("fullName", O_CREAT, 0666, 0);//是否有售出票
	pthread_create(&p1, NULL, worker1, NULL);
	pthread_create(&p2, NULL, worker2, NULL);
	pthread_join(p2, NULL);
	pthread_join(p1, NULL);


	printf("The number of ticketCount is :%d\n", ticketCount);
	sem_close(empty);
	sem_close(full);
	sem_unlink("emptyName");
	sem_unlink("fullName");
	return 0;
}
