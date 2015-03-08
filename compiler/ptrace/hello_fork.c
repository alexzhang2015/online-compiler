#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
	pid =  fork();
	if (pid != 0)
	{
	    printf("parent:hello world!\n");
	}
	else
	{
	    printf("child:hello world!\n");
	}
		
	return 0;
}
