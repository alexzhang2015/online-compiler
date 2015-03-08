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

///////////////////////////////////////////////////////////////////////////
Use ptrace() to trace the process ,and monitor the   (__NR_exit_group 252) syscall,
then parser the /proc/process-pid/status ,get VmPeak virtual memory size ,
that's what i what.       2011.04.07

test:
Process executed system call ID = 4 with return value= 13
catch the exit syscall
path_name:/proc/789/status
Get the VmPeak VIrtual Memory
 VmPeak:            1636 kB
Process executed system call ID = 252
///////////////////////////////////////////////////////////////////////////
*/

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <sys/reg.h>   /* For constants
                                 //  ORIG_EAX etc */

using namespace std;

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
            wait(&val); //wait the signals.
            if(WIFEXITED(val)) //judge if the child process exit.
                return 0; 
            if(flag==0) //get the signals for child process call a syscall.
            { 
                orig_eax=ptrace(PTRACE_PEEKUSER, child, ORIG_EAX*4, NULL); 
				if (orig_eax == 252)
				{
				    printf("catch the exit syscall\n");
					char path_name[30];
					char path[10] = "/proc/";
					char pid_buf[10];
					snprintf(pid_buf, 10, "%d", child);
					strcpy (path_name, path);
					strcat (path_name, pid_buf);
					strcat (path_name, "/status");
					cout << "path_name:" << path_name << endl;
					ifstream  status_file;
					string tmp;
					status_file.open (path_name);
					if (status_file.is_open())
					{
						std::cout << "Get the VmPeak VIrtual Memory\n " ;
		
						while (!status_file.eof())
						{
							getline(status_file, tmp);
							/*
							*list the information by match the card_id!
							*/
							if (tmp.find("VmPeak") != string::npos)
							{
								cout << tmp << endl;
							}
							//cout << "process file\n";
						}
					}
					else
					{
					    std::cout << "file open failed\n";
					}
					status_file.close();
				}
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
