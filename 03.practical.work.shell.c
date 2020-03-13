#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void parseArg(char *cmd, char **argv)
{
	while (*cmd != '\0') 
	{       
		while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n') *cmd++ = '\0';
		*argv++ = cmd;
		while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t' && *cmd != '\n') cmd++;
	}
	*argv = '\0';
}

int main()
{
	char cmd[255];
	char *argv[16];

	while (1) 
	{                   
		printf("Command: ");
		gets(cmd);
		parseArg(cmd, argv);
		if (strcmp(argv[0], "quit") == 0) exit(0);
		
		int pid;
		int done;

		if ((pid = fork()) < 0) exit(1);
		else if (pid == 0) 
		{
			if (execvp(*argv, argv) < 0) 
			{
				printf("Undefined command. Please try again... \n");
				exit(1);			
			}
		}
		else 
		{                                  
			while (wait(&done) != pid)       
			;
		}
		printf("\n");
	}
}
