/*
ptrace - process trace
#include <sys/ptrace.h>
long ptrace(enum __ptrace_request request, pid_t pid,             void
*addr, void *data);

The ptrace() system call provides a means by which a parent process may observe and 
control the execution of another process, and examine and change its core image and registers. 
It is primarily used to implement breakpoint debugging and system call tracing.

This demo mainly test PTRACE_SYSCALL __ptrace_request,print all the hello's syscalls .
Using PTRACE_SYSCALL can trace every syscalls of code. 2011.04.06

PS:
orig_eax=ptrace(PTRACE_PEEKUSER, child, ORIG_EAX*4, NULL); 
Use this way get the linux kernel syscall ID(syscalls.h),--> Software interrupt.
And the linux syscalls differs from POSIX API (unistd.h).
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/reg.h>   /* For constants
                                 //  ORIG_EAX etc */
int main()
{   pid_t child;
    long orig_eax;
    child = fork();
	int val;
	int flag=0;
    if(child == 0) 
	{
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./hello_fork", "hello_fork", NULL);
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
				if (orig_eax == 120)
				    printf("catch the clone syscall\n");
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
