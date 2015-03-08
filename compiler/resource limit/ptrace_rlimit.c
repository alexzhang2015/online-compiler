/*
ptrace - process trace
#include <sys/ptrace.h>
long ptrace(enum __ptrace_request request, pid_t pid,             void
*addr, void *data);

The ptrace() system call provides a means by which a parent process may observe and 
control the execution of another process, and examine and change its core image and registers. 
It is primarily used to implement breakpoint debugging and system call tracing.

Resource limits are preserved across execve();A major step of online-compiler.
Combining the resource limit and ptrace .Meanwhile the father process handling 
of child process doesn't affect the child process's CPU_LIMIT .    2011.04.08

*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/reg.h>   /* For constants
                                 //  ORIG_EAX etc */
int main()
{   pid_t child;
    long orig_eax;
	struct rlimit r;
    child = fork();
	int val;
	int flag=0;
    if(child == 0) 
	{
        
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
	 
		char *prog[] = {"./hello1", NULL};
		char *env[] = {"USER=alex", "PATH=/home", NULL};
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(prog[0], prog, env);

    }
    else 
	{
        wait(NULL);
        orig_eax = ptrace(PTRACE_PEEKUSER,
                          child,ORIG_EAX*4,
                          NULL);
        printf("The child made a "
               "system call %ld\n", orig_eax);
        //ptrace(PTRACE_CONT, child, NULL, NULL);
		ptrace(PTRACE_SYSCALL,child,NULL,NULL); 
		while(1) 
        { 
            wait(&val); //wait the signals.
            if(WIFEXITED(val)) //judge if the child process exit.
                return 0; 
            if(flag==0) //get the signals for child process call a syscall.
            { 
                orig_eax=ptrace(PTRACE_PEEKUSER, child, ORIG_EAX*4, NULL); 
				if (orig_eax == -1)
				    return 0; 
                printf("Process executed system call ID = %ld ",orig_eax); 
                flag=1; 
            } 
            else //get the signals for child process exit a syscall.
            { 
                orig_eax=ptrace(PTRACE_PEEKUSER, child, EAX*4, NULL); 
                printf("with return value= %ld\n", orig_eax); 
                flag=0; 
            } 
            ptrace(PTRACE_SYSCALL,child,NULL,NULL); 
		}
    }
    return 0;
}
