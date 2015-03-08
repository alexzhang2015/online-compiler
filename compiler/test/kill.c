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
    pid_t pid;
pid_t child_pid;
    struct timeval st,et;
    int  i;
    float timeuse;
    char *message;
    int n;
    int exit_code;

    printf("fork program starting\n");
    pid = fork();
    if (pid==0)
    {
    system(" sleep(5)") ;
    pid=getpid();
    printf("child pid%d\n",pid);
   sleep(5);
   
   printf("child over!");
    
    }
    if (pid!=0)
    {
    //gettimeofday(&st,NULL);
     
     system("ps -a |grep   top  > systemthread");
     sleep(2);
                            ifstream kill ("  systemthread");
                            if(kill .is_open()){
                                cerr<<"  open the killsystemthread file "<<endl;
                                
                            }
                            int systemthreadpid;
                            kill >>systemthreadpid;
                             cout<<systemthreadpid;
                          //  kill(systemthreadpid,SIGTERM);
 //   i=kill(pid,SIGKILL);
    pid=getpid();
   // printf("%d",pid);
    if(i<0)
    printf("kill failed!\n");
    if(i==0)
    printf("kill success!\n");
    }
// int stat_val;               //等待 用户进程结束，int stat_val ,定义了，用户一个入口地址，父进程等待子进程从&stat_val 指针入口地址
 //child_pid = wait(&stat_val);//进入，一直等到结束时候，子进程发来结束信号，软中断，(linux中进程间通信的基础),父进程从该断点继续执行下去。
			     //child_pid 为父进程中记录
/*    switch(pid) 	     //的子进程的pid .
    
    {
    case -1:
  //      exit(1);
    case 0:
        message = "This is the child";
        n = 5;
        exit_code = 37;
        break;
    default:
        message = "This is the parent";
        n = 3;
        exit_code = 0;
        break;
    }

    for(; n > 0; n--) {
        puts(message);
        sleep(1);
    }

/*  This section of the program waits for the child process to finish.  

    if(pid) {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }
    exit (exit_code);*/
return 0;
}
