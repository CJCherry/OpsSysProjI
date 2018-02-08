#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

void execute(char ** cmd);
void redirectOutput();
void redirectInput();

int main()
{
	int Functionreturn = 0;
	char Echokey[] = "echo";
	char str[256];
	char cmd[256];
	do
	{	
		PrintPrompt();
		scanf("%s", cmd);
   		fgets(str, 255, stdin);
		
		printf("You said: ");
		fputs(cmd, stdout);
		fputs(str, stdout);
		if(strcmp(Echokey,cmd) == 0)
		{
			Functionreturn = Echo(str);
		}
		else if(cmd[0] == "$")
		{
			Functionreturn = EnviornVariables(cmd);
		}
		else if(strcmp(cmd,"exit") == 0)
		{
			printf("Exiting Shell");
			return 0;
		}
	} while(1);
	
	//for testing
	char programPath[] = "/home/majors/aanderso/COP4610/Proj1/a.out";
	char * argv[] = {programPath, NULL, NULL, NULL};
	
	//test calls
	//execute(argv);
	//redirectOutput();
	//redirectInput();

}

int Echo(char* str)
{
	fputs(str, stdout);
	return 0;
}

int EnviornVariables(char* cmd)
{
	memmove(cmd, cmd+1, strlen(cmd));
	printf("%s/n", getenv(cmd));
	return 0;
}

int PrintPrompt()
{
	printf("%s@%s :: %s => ", getenv("USER"), getenv("MACHINE"), getenv("PWD"));
	return 0;
}

//works
void execute(char ** cmd) {
	int status;
	pid_t pid = fork();
	if (pid == -1) {
		printf("err");
		exit(1);
	}
	else if (pid == 0) {
		//child
		//cmd[0] is absolute pathname
		//cmd is arguments
		//ex: char *cmd[4] = { “/bin/ls”, “-l”, “-a”, NULL };
		execv(cmd[0], cmd);
		//if error executing:
		printf("Problem executing %s\n", cmd[0]);
		exit(1);
	}
	else {
		//parent
		//status?
		//wait until child finishes
		waitpid(pid, &status, 0);
	}
}

//works
void redirectOutput () {
	//parse filenames
	
	//program to get output from
	char programPath[] = "/home/majors/aanderso/COP4610/Proj1/a.out";
	char * argv[] = {programPath, NULL, NULL, NULL};
	
	//for testing, file to redirect output to
	char filePath[] = "/home/majors/aanderso/COP4610/Proj1/output.txt";
	
	//file desc table for output.txt
	//O_WRONLY = write mode
	//O_CREAT = if file dne, create it
	int fdSpot = open(filePath, O_WRONLY | O_CREAT);
	
	//fork creates another file descr table
	if (fork() == 0) {
		//child
		
		//close stdout
		close(STDOUT_FILENO);
		//fdSpot replaces stdout
		dup(fdSpot);
		close(fdSpot);
		execute(argv);
	}
	else {
		//parent
		close(fdSpot);
	}
}

//works
void redirectInput () {
	//for testing, program to redirect input to
	char programPath[] = "/home/majors/aanderso/COP4610/Proj1/a.out";
	char * argv[] = {programPath, NULL, NULL, NULL};
	
	//for testing, file to get input from
	char filePath[] = "/home/majors/aanderso/COP4610/Proj1/input.txt";
	
	int fdSpot = open(filePath, O_RDONLY);
	
	//fork creates another file descr table
	if (fork() == 0) {
		//child
		close(STDIN_FILENO);
		dup(fdSpot);
		close(fdSpot);
		execute(argv);
	}
	else {
		//parent
		close(fdSpot);
	}
}