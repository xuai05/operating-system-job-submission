#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	pid_t pid;
	pid = fork();	
	if (pid > 0) while (1);
	else if (pid == 0){
		int ret;
		ret = execlp("vi", "", NULL);
		if (ret == -1){
			perror("execl");
			printf("excel error\n");
		}
	}
	else if (pid == -1){
		perror("fork");
		printf("fork error\n");
	}
}