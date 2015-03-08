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
void ding(int sig)
{
cout<<"hh\n";
}
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
     
    pid=getppid();   //child process 
    printf("child pid%d\n",getppid());
    sleep(5);
   // kill(pid,SIGALRM);
 //    sleep(5 );
   //   sleep(5 );
  // while (1){sleep(1);}
  //  printf("jjj\n");
 //  printf("child over!");
  
    }
    else if (pid!=0)
    {
    //(void) signal(SIGALRM,ding);
    // pause();
  	printf("child pid%d\n",pid);
  	printf("father pid%d\n",getpid());
     printf("father success!\n");
    //  sleep(5 );
     // kill(pid,SIGTERM);
    //     wait(&abc);          
    //   waitpid(pid,&abc,WUNTRACED);       
 	sleep(10);
    printf("father success!\n");
    exit(0);
    }
 
             


}
