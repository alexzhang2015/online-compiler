/*
////////////////////////////////////////////////////////////////////////////
#include <sys/time.h>
#include <sys/resource.h>
int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);

struct rlimit {
    rlim_t rlim_cur;  // Soft limit 
    rlim_t rlim_max;  // Hard limit (ceiling for rlim_cur) 
};

RLIMIT_CPU
CPU time limit in seconds. When the process reaches the soft limit, it is sent a SIGXCPU signal. 
The default action for this signal is to terminate the process. However, the signal can be caught, 
and the handler can return control to the main program. If the process continues to consume CPU time, 
it will be sent SIGXCPU once per second until the hard limit is reached, at which time it is sent SIGKILL. 
(This latter point describes Linux 2.2 through 2.6 behaviour. Implementations vary in how they treat processes 
which continue to consume CPU time after reaching the soft limit. Portable applications that need to catch 
this signal should perform an orderly termination upon first receipt of SIGXCPU.)

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
test ,2011.04.03  CentOS5.3
set child process
1.Soft limit = 1s   ;When cpu time reaches it ,kernel will send the SIGXCPU signal to the child process.
2.Hard limit = 2s   ;

To the SOft limit situation ,
1.If child process capture the signal ,
(void) signal(SIGXCPU,ding); then process continues to consume CPU time,it will be sent SIGXCPU once per 
second until the hard limit is reached, at which time it is sent SIGKILL. 
2.If the child process doesn't capture the signals ,
then the default action for this signal(SIGXCPU) is to terminate the process.

result:
[alex:onlinecompiler]# time ./RLIMIT_CPU |grep "SIGXCPU"
The SIGXCPU signal caught

real    0m3.163s
user    0m1.403s
sys     0m1.710s
//annote the (void) signal(SIGXCPU,ding); 
[alex:onlinecompiler]# g++ -o RLIMIT_CPU RLIMIT_CPU.cpp
[alex:onlinecompiler]# time ./RLIMIT_CPU |grep "SIGXCPU"

real    0m1.727s
user    0m0.782s
sys     0m0.929s
//////////////////////////////////////////////////////////////////////////////

PS:
1.The cpu time of RLIMIT_CPU means the process's real obtained cpu time slice,
Through the linux time command ,just the (user + sys) time .
user : user cpu time 
sys : system cput time
User CPU time is time spent on the processor running your program's code (or code in libraries), running in the user mode.
system CPU time is the time spent running code in the operating system kernel on behalf of your program, 
Like calling the syscalls, running in the kerner mode.

2.How to get user CPU time and system cpu time by linux api.
#include <sys/times.h>
clock_t times(struct tms *buf);  

DESCRIPTION
The times() function stores the current process times in the struct tms that buf points to. The struct tms is as defined in <sys/times.h>:
struct tms {
clock_t tms_utime;  // user time 
clock_t tms_stime;  // system time 
clock_t tms_cutime; // user time of children 
clock_t tms_cstime; // system time of children 
};

the user CPU time (the sum of the tms_utime and tms_cutime values in a struct tms as returned by times(2))
the system CPU time (the sum of the tms_stime and tms_cstime values in a struct tms as returned by times(2)).  	

3.fork()
Child process will keep the RLIMIT_CPU if Father set RLIMIT_CPU before call fork().
A child process created via fork(2) inherits its parents resource limits. Resource limits are preserved across execve(2).

4./proc/[pid]/limits (since kernel 2.6.24)
              This file displays the soft limit, hard limit, and units of measurement
              for each of the process's resource limits (see getrlimit(2)).  The file
              is protected to only allow reading by the real UID of the process.
			  
5.ulimit  command
*/


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
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>



using namespace std;


void ding(int sig)
{

      
        cout   << "parent:the compiler process just over!"
           << endl;

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
    struct rlimit r;
	
    printf("fork program starting\n");
	 if(getrlimit(RLIMIT_CPU,&r)<0)
     {
         fprintf(stderr,"getrlimit error\n");
         exit(1);
     }
     if (r.rlim_cur == RLIM_INFINITY )
     printf("RLIMIT_CPU.rlim_cur: no limit on resource.\n");
     else
     printf("RLIMIT_CPU cur:%ld\n",r.rlim_cur);
     if (r.rlim_max == RLIM_INFINITY)
     printf("RLIMIT_CPU.rlim_max: no limit on resource.\n");
     else
     printf("RLIMIT_CPU:%ld\n",r.rlim_max);

     
     //r.rlim_cur=1;  //s
     //r.rlim_max=2;
     if (setrlimit(RLIMIT_CPU,&r)<0)
     {
         fprintf(stderr,"setrlimit error\n");
         exit(1);
     }

     /** get value of set **/
     if(getrlimit(RLIMIT_CPU,&r)<0)
     {
         fprintf(stderr,"getrlimit error\n");
         exit(1);
     }
     printf("RLIMIT_CPU:%ld\n",r.rlim_cur);
     printf("RLIMIT_CPU:%ld\n",r.rlim_max);
     
	 
    pid =  fork();
	 
	if (pid!=0)
    {
    int hh;
	
      wait(&hh);
     
     //sleep(1 );
                          
             
 
    printf("father success!\n");
    exit(0);
    }
	
    if (pid==0)
    {
     
    pid=getpid();
    printf("child pid%d\n",pid);

    r.rlim_cur=1;  //s
    r.rlim_max=2;
     if (setrlimit(RLIMIT_CPU,&r)<0)
     {
         fprintf(stderr,"setrlimit error\n");
         exit(1);
     }
	if(getrlimit(RLIMIT_CPU,&r)<0)
     {
         fprintf(stderr,"getrlimit error\n");
         exit(1);
     }
     if (r.rlim_cur == RLIM_INFINITY )
     printf("RLIMIT_CPU.rlim_cur: no limit on resource.\n");
     else
     printf("RLIMIT_CPU cur:%ld\n",r.rlim_cur);
     if (r.rlim_max == RLIM_INFINITY)
     printf("RLIMIT_CPU.rlim_max: no limit on resource.\n");
     else
     printf("RLIMIT_CPU:%ld\n",r.rlim_max);
     
    
    for(int i=0; i < 331000000; i++)
	{
	   (void) signal(SIGXCPU,ding);
		cout << i
		     << ":hello world!"
		     << endl;
	    
	}
    printf("Can i print out!\n");
    
    
    }

 
             
 
return 0;
}

   
