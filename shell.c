#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/time.h>

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
