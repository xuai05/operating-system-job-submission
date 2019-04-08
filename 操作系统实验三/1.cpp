#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include<fcntl.h>
#include<semaphore.h>
#include<pthread.h>

sem_t *a = NULL;
sem_t *b = NULL;
sem_t *c = NULL;
sem_t *d = NULL;


int main(void)
{
	a = sem_open("a", O_CREAT, 0666, 0);
	b = sem_open("b", O_CREAT, 0666, 1);
	c = sem_open("c", O_CREAT, 0666, 0);
	d = sem_open("d", O_CREAT, 0666, 0);
	//printf("I am the process P1,PID is %d.\n",getpid());
	pid_t pid1 = fork();
	if (pid1 == 0){
		printf("I am the process P1£¬PID is %d.\n", getpid());
		sem_post(a);
		exit(1);
		printf("You should never see this.\n");
	}
	pid_t pid2 = fork();
	if (pid2 == 0){
		sem_wait(a); sem_wait(b);
		printf("I am the process P2£¬PID is %d.\n", getpid());
		sem_post(b); sem_post(c); sem_post(a);
		exit(1);
		printf("You should never see this.\n");
	}
	pid_t pid3 = fork();
	if (pid3 == 0){
		sem_wait(a); sem_wait(b);
		printf("I am the process P3£¬PID is %d.\n", getpid());
		sem_post(b); sem_post(d); sem_post(a);
		exit(1);
		printf("You should never see this.\n");
	}
	pid_t pid4 = fork();
	if (pid4 == 0){
		sem_wait(c); sem_post(d);
		printf("I am the process P4£¬PID is %d.\n", getpid());
		exit(1);
		printf("You should never see this.\n");
	}
	sem_close(a);
	sem_close(b);
	sem_close(c);
	sem_close(d);
	sem_unlink("a");
	sem_unlink("b");
	sem_unlink("c");
	sem_unlink("d");
	return 0;
}

