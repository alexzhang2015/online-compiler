#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <signal.h>
using namespace std;
int main()
{
int abc;
    pid_t pid;
pid_t child_pid;
    struct timeval st,et;
    int  i;
    float timeuse;
    char *message;
    int n;
    int exit_code;
 
    printf("fork program starting\n");
     pid =  fork();
    if (pid==0)
    {
     
    pid=getpid();
    printf("child pid%d\n",pid);
   if(system("find /var/www/exec/exec") )
   	printf("find create system()\n");
  // while (1){}
  //  printf("jjj\n");
 //  printf("child over!");
    
    }
    if (pid!=0)
    {
    int hh;
      wait(&hh);
     
     sleep(1 );
                          
             
 
    printf("father success!\n");
    exit(0);
    }
 
             
 
return 0;
}
