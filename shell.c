#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
	char str[256];
	do
	{	
		PrintPrompt();
   		fgets(str, 255, stdin);
		
		printf("You said: ");
		fputs(str, stdout);
		if(strcmp(str,"exit"))
		{
			return 0;
		}
	} while(1);

}

void PrintPrompt()
{
	printf("%s@%s :: %s => ", getenv("USER"), getenv("MACHINE"), getenv("PWD"));
}
