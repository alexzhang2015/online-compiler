#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{	
	//system("ls -la");
	execl("/usr/bin/gcc", "/usr/bin/gcc", "-o",  (char *) 0);
    printf("Command done!");
return 0;
}
