#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	char cmd[255];
	
	while (1)
	{
		printf("Command: ");
		scanf("%s", cmd);

		if (cmd == "quit") return 0;

		int pid = fork();
		if (pid == 0)
		{
			char *args[] = {cmd, NULL};
           		execvp(cmd, args);
        	}
		else 
		{
			wait(NULL);
			printf("\n");
		}
    	}	
	return 0;
}
