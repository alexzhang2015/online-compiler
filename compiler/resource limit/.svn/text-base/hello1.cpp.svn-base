#include <iostream>
#include <unistd.h>
#include <sys/resource.h>

using namespace std;

int main()
{
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
	
	
	for(int i=0; i < 331000000; i++)
	{
	  // (void) signal(SIGXCPU,ding);
		cout << i
		     << ":hello world!"
		     << endl;
	    
	}
	
	return 0;
}
