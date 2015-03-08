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

RLIMIT_AS
The maximum size of the process's virtual memory (address space) in bytes. 
This limit affects calls to brk(2), mmap(2) and mremap(2), which fail with 
the error ENOMEM upon exceeding this limit. Also automatic stack expansion will fail 
(and generate a SIGSEGV that kills the process if no alternate stack has been made available 
via sigaltstack(2)). Since the value is a long, on machines with a 32-bit long either this 
limit is at most 2 GiB, or this resource is unlimited.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
test ,2011.04.03  CentOS5.3
// set limit 1M  virtual memory ,failure Alloc memory failure
     r.rlim_cur=1000000;  //bytes
     r.rlim_max=2000000;
[alex:onlinecompiler]# gcc -o RLIMIT_AS RLIMIT_AS.c
[alex:onlinecompiler]# ./RLIMIT_AS
_TEXT_RLIMIT_.rlim_cur: no limit on resource.
_TEXT_RLIMIT_.rlim_max: no limit on resource.
_TEXT_RLIMIT_cur:1000000
_TEXT_RLIMIT_max:2000000
Alloc memory failure !
Can i print out!

// set limit 10M  virtual memory ,Success alloc memory!
     r.rlim_cur=10000000;  //bytes
     r.rlim_max=20000000;
[alex:onlinecompiler]# vim RLIMIT_AS.c
[alex:onlinecompiler]# gcc -o RLIMIT_AS RLIMIT_AS.c
[alex:onlinecompiler]# vim RLIMIT_AS.c
[alex:onlinecompiler]# ./RLIMIT_AS
_TEXT_RLIMIT_.rlim_cur: no limit on resource.
_TEXT_RLIMIT_.rlim_max: no limit on resource.
_TEXT_RLIMIT_cur:10000000
_TEXT_RLIMIT_max:20000000
Success alloc memory!
Can i print out!

*/


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>

#define _TEXT_RLIMIT_ RLIMIT_AS

int main(void)
{

     struct rlimit r;
     if(getrlimit(_TEXT_RLIMIT_,&r)<0)
     {
         fprintf(stderr,"getrlimit error\n");
         exit(1);
     }
     if (r.rlim_cur == RLIM_INFINITY )
     printf("_TEXT_RLIMIT_.rlim_cur: no limit on resource.\n");
     else
     printf("RLIMIT_AS cur:%ld\n",r.rlim_cur);
     if (r.rlim_max == RLIM_INFINITY)
     printf("_TEXT_RLIMIT_.rlim_max: no limit on resource.\n");
     else
     printf("_TEXT_RLIMIT_max:%ld\n",r.rlim_max);

     // set limit 1M  virtual memory ,failure Alloc memory failure
     // set limit 10M  virtual memory ,Success alloc memory!
     r.rlim_cur=1000000;  //bytes
     r.rlim_max=2000000;
     if (setrlimit(_TEXT_RLIMIT_,&r)<0)
     {
         fprintf(stderr,"setrlimit error\n");
         exit(1);
     }

     /** get value of set **/
     if(getrlimit(_TEXT_RLIMIT_,&r)<0)
     {
         fprintf(stderr,"getrlimit error\n");
         exit(1);
     }
     printf("_TEXT_RLIMIT_cur:%ld\n",r.rlim_cur);
     printf("_TEXT_RLIMIT_max:%ld\n",r.rlim_max);
     
     //test the RLIMIT_AS
     char * buffer;
     buffer = (char*) malloc (10);
     if (buffer == NULL)
     {
         printf("Alloc memory failure !\n");
     }
     else
     {
         printf("Success alloc memory!\n");
         free(buffer);
         buffer = NULL;
     }
    
    printf("Can i print out!\n");
     return 0;
}               

                                                                                                                                 