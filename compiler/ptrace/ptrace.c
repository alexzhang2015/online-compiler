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
        execl("./hello", "hello", NULL);
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
            wait(&val); //等待信号 
            if(WIFEXITED(val)) //判断子进程是否退出 
                return 0; 
            if(flag==0) //第一次(进入系统调用)，获取系统调用的参数 
            { 
                orig_eax=ptrace(PTRACE_PEEKUSER, child, ORIG_EAX*4, NULL); 
                printf("Process executed system call ID = %ld ",orig_eax); 
                flag=1; 
            } 
            else //第二次(退出系统调用)，获取系统调用的返回值 
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
