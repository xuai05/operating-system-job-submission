#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>

int main(int argc, char *argv) {
	/*
	�ȴ�ӡ���ڵ�
	*/
	pid_t p1;

	if (p1 == 0){
		/*
		�������p1
		*/
		int p1pid, p1ppid;
		p1pid = getpid();
		p1ppid = getppid();
		//printf("p1 pid: %d, ppid: %d\n", getpid(),getppid());
		pid_t p3;
		/*
		�ȴ���p3
		*/
		p3 = fork();
		if (p3 == 0){
			/*
			j�������p3
			*/
			int i;
			for (i = 0; i<10; i++){
				printf("p3 pid: %d, ppid: %d\n", getpid(), getppid());
				sleep(1);
			}
			return 0;
		}
		else if (p3 > 0){
			/*
			����p3�ĸ����̣�Ҳ����p1��
			��������������p2
			*/
			pid_t p2;
			p2 = fork();
			if (p2 == 0){
				/*
				�������p2,�������ȴ���p4
				*/
				pid_t p4;
				p4 = fork();
				if (p4 == 0){
					/*
					�������p4
					*/
					int i;
					for (i = 0; i<10; i++){
						printf("p4 pid: %d, ppid: %d\n", getpid(), getppid());
						sleep(1);
					}
					return 0;

				}
				else if (p4 >0){
					/*
					�˴�λ��p4�ĸ����̣���p2,��������p5
					*/
					pid_t p5;
					p5 = fork();
					if (p5 == 0){
						//p5
						int i;
						for (i = 0; i<10; i++){
							printf("p5 pid: %d, ppid: %d\n", getpid(), getppid());
							sleep(1);
						}
						return 0;
					}

					else{
						//p2
						int i;
						for (i = 0; i<10; i++){
							//ͨ��exit()��ֹp2
							if (i == 2)
								exit(1);
							printf("p2 pid: %d, ppid: %d\n", getpid(), getppid());
							sleep(1);
						}
						return 0;
					}
				}
			}
		}
		int i;
		for (i = 0; i<10; i++){
			printf("p1 pid: %d, ppid: %d\n", getpid(), getppid());
			sleep(1);
		}
		return 0;
	}
	sleep(1);
}
