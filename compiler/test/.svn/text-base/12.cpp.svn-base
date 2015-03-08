#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <cstring>
using namespace std;
int main()
{
	string command,line="hello";
	char * cmd;
	pid_t pid1,pid2;
	pid1=fork();
	int stat;
	pid2=wait(&stat);
	if(pid1==0){
	
	for(int i=0;i<100;i++)
        cout<<"it's a child process"<<endl;
 	command.append("g++  ");
        command+=line;
        command.append("   -o   ");
        command.append("/var/www/exec/exec") ;
        cmd = new char [command.size()+1];

        strcpy(cmd,command.c_str());                //convert string to char*
     //   system(cmd);
        cout<<cmd<<endl;
        delete[] cmd;
        
        }
        if(pid1!=0)
        {
        for(int i=0;i<10;i++)
        cout<<"it's a parent process"<<endl;
        }
        return 0;
}
