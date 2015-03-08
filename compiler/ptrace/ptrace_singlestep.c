/*
ptrace - process trace
#include <sys/ptrace.h>
long ptrace(enum __ptrace_request request, pid_t pid,             void
*addr, void *data);

The ptrace() system call provides a means by which a parent process may observe and 
control the execution of another process, and examine and change its core image and registers. 
It is primarily used to implement breakpoint debugging and system call tracing.

This demo mainly test 
PTRACE_SINGLESTEP __ptrace_request,print all the hello's instructions .
using PTRACE_SINGLESTEP can trace every instructions of code. 2011.04.06
PTRACE_GETREGS Copies the child's general purpose or floating-point registers, 
respectively, to location data in the parent. 
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/user.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/reg.h>   /* For constants
                                 //  ORIG_EAX etc */
								 
int main()
{   pid_t child;
    const int long_size = sizeof(long);
    child = fork();
    if(child == 0) 
	{
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./hello", "hello", NULL);
    }
	
    else 
	{
        int status;
        union u 
		{
            long val;
            char chars[long_size];
        }data;
        struct user_regs_struct regs;
        int start = 0;
        long ins;
        while(1) 
		{
            wait(&status);
            if(WIFEXITED(status))
                break;
            ptrace(PTRACE_GETREGS,
                   child, NULL, &regs);
            if(start == 1) 
			{
                ins = ptrace(PTRACE_PEEKTEXT,
                             child, regs.eip,
                             NULL);
                printf("EIP: %lx Instruction "
                       "executed: %lx\n",
                       regs.eip, ins);
            }
            if(regs.orig_eax == SYS_write)   //print all instructions after SYS_write syscalls.
			{
                start = 1;
                ptrace(PTRACE_SINGLESTEP, child,
                       NULL, NULL);
            }
            else
                ptrace(PTRACE_SINGLESTEP, child,
                       NULL, NULL);
        }
    }
    return 0;
}
