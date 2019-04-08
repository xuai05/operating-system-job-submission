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

void *worker1(void *arg){//��Ʊ����
	for (int i = 0; i<30; i++){
		sem_wait(empty);
		//��Ʊ���̹ؼ�����
		temp = ticketCount;
		pthread_yield();
		temp = temp - 1;
		pthread_yield();
		ticketCount = temp;
		printf("after the Sell,the number of ticketCount is :%d\n", ticketCount);
		sem_post(full);
	}
}
void *worker2(void *arg){//��Ʊ����
	for (int i = 0; i<10; i++){
		sem_wait(full);
		//��Ʊ���̹ؼ�����
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
	pthread_t p1, p2;//������������
	empty = sem_open("emptyName", O_CREAT, 0666, 1000);//Ʊ���Ƿ�Ϊ��
	full = sem_open("fullName", O_CREAT, 0666, 0);//�Ƿ����۳�Ʊ
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
