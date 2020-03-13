#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int pid;
int done;

void handler(int signal_num)
{
	printf("\nSignal %d\n", signal_num);
	if (signal_num == SIGTSTP)
		if (pid == 0) 
		{
			signal(SIGTERM, handler);
			exit(0);
		}
}

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
	FILE *f = fopen("command.log", "a");

	char cmd[255];
	char *argv[16];

	signal(SIGTSTP, handler); 

	while (1) 
	{           
		printf("Command: "); 
		
		gets(cmd);


		fputs(cmd, f);
		fputs("\n", f);

		parseArg(cmd, argv);
		if (strcmp(argv[0], "quit") == 0) exit(0);

		pid = fork();

		if (pid < 0) exit(1);
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

	fclose(f);

	return 0;
}
