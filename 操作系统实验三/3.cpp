#include<fcntl.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

volatile int buf[5];
volatile int N = 5;
sem_t *buf_empty = NULL;
sem_t *buf_data = NULL;


void *input(void *arg){
	for (int i = 0; i<N; i++, i = i%N){
		i = i%N;
		sem_wait(buf_empty);
		printf("input:\n");
		scanf("%d", &buf[i]);
		sem_post(buf_data);
	}
}

void *output(void *arg){
	for (int i = 0; i<N; i++, i = i%N){
		sem_wait(buf_data);
		printf("output:%d\n", buf[i]);
		sleep(1);
		sem_post(buf_empty);
	}
}


int main(int argc, char *argv[]){
	pthread_t p1, p2;
	sem_close(buf_empty);
	sem_close(buf_data);
	sem_unlink("mySemempty");
	sem_unlink("mySemdata");
	buf_empty = sem_open("mySemempty", O_CREAT, 0666, 5);
	buf_data = sem_open("mySemdata", O_CREAT, 0666, 0);
	pthread_create(&p1, NULL, input, NULL);
	pthread_create(&p2, NULL, output, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	return 0;
}
