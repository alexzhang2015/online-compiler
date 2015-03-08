/*
 * Copyright (C) 2011 ALex Zhang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <signal.h>
#include <boost/lexical_cast.hpp>
#include "handlewrong.h"
#include "block_syscalls.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/times.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/reg.h>   /* For constants
								//  ORIG_EAX etc */
								 


using namespace std;



//CPP  and c file ,0.1s ,and it will just output 1M file at most in the limited time!
#define CFILERUNTIME  100000
#define CPPFILERUNTIME 100000
#define PYTHONFILERUNTIME 700000
#define HASKELLFILERUNTIME 100000
#define PROLOGFILERUNTIME  700000
#define LUAFILERUNTIME  700000
#define JAVAFILERUNTIME  1500000
#define GOFILERUNTIME  200000

const int C_FILE = 1;
const int CPP_FILE = 2;
const int PYTHON_FILE = 3;
const int HASKELL_FILE = 4;
const int PROLOG_FILE = 5;
const int LUA_FILE = 6;
const int JAVA_FILE = 7;
const int GO_FILE = 8;


//set the file_name Global name ,for log convenience.
string filename;

//Handle exec file timeout!
void handle_timeout(string exec_name);

//Handle python timeout!
void handle_python_timeout(string exec_name);

//Handle prolog timeout!
void handle_prolog_timeout(string exec_name);

//Handle lua timeout!
void handle_lua_timeout(string exec_name);

//Handle java timeout!
void handle_java_timeout(string exec_name);

//Handle go timeout!
void handle_go_timeout(string exec_name);


//let parent go ahead ,if compiler process over!
void ding(int sig)
{

	cout << filename
		 << ":"
		 << "Parent:the compiler process just over!"
		 << endl;

}


/** 
 * Get The file's type! Return the attribute number.
 */
int get_file_attribute(string &file_name)
{

	if ( file_name.find("cpp") != string::npos)      
	{
		return CPP_FILE;
	}
	else if ( file_name.find("py") != string::npos)
	{
		return PYTHON_FILE;
	}
	else if ( file_name.find("hs") != string::npos)
	{
		return HASKELL_FILE;
	}
	else if ( file_name.find("pl") != string::npos)
	{
		return PROLOG_FILE;
	}
	else if ( file_name.find("lua") != string::npos)
	{
		return LUA_FILE;
	}
	else if ( file_name.find("java") != string::npos)
	{
		return JAVA_FILE;
	}
	else if ( file_name.find("go") != string::npos)
	{
		return GO_FILE;
	}
	else 
	{
		return C_FILE;
	}
}


int main(int argc, char *argv[])
{
	// Get the file name of compiler or interpret .
	filename = *(argv + 1);

	pid_t pid_c, pid_cpp, pid_python, pid_haskell, pid_prolog, pid_lua, pid_java, pid_go;
	int file_type = 0;
	cout << "\n\n\n";
	//Get the date!
	time_t time_val;
	(void) time(&time_val);
	cout << ctime(&time_val) ;

	cout << filename 
		 << ":"
		 << "system start!" 
		 << endl;
       
	//The illegal_wrong_file keep the wrong info for the illegal file.
	string illegal_wrong_file;
	illegal_wrong_file.append("/var/www/output/wrong.");
	illegal_wrong_file.append(std::string( *(argv + 1)));

	//The compiler_interpret_wrong_file to log the wrong info during the compiler or interpret process.
	string compiler_interpret_wrong_file;
	compiler_interpret_wrong_file.append("/var/www/output/wrong.");
	compiler_interpret_wrong_file.append(std::string( *(argv + 1)));
	
	//The compiler_time_file keep the compiler process time. 
	string compiler_time_file;
	compiler_time_file.append("/var/www/output/compilertime." );
	compiler_time_file.append(std::string(*(argv + 1)));
	
	//The stdin_file keep the stdin from user.
	string stdin_file;
	stdin_file.append("/var/www/output/stdin." );
	stdin_file.append(std::string(*(argv + 1)));
	
	//The out_file keep the result after exec or interpret code.
	string out_file;
	out_file.append("/var/www/output/out." );
	out_file.append(std::string(*(argv + 1)));
	
	//The runtime_file keep the running time of exec or interpret.
	string runtime_file;
	runtime_file.append("/var/www/output/runtime.");
	runtime_file.append(std::string( *(argv + 1)));

	//The momery keep the running momery of exec.
	string momery_file;
	momery_file.append("/var/www/output/momery.");
	momery_file.append(std::string( *(argv + 1)));
	
	
	//Create wrong_file in advance.
	ofstream wrong_file_create;
	wrong_file_create.open (compiler_interpret_wrong_file.c_str());
	wrong_file_create << "";
	wrong_file_create.close();
 
	//Create out_file in advance.
	ofstream out_file_create;
	out_file_create.open (out_file.c_str());
	out_file_create << "";
	out_file_create.close();
 
	//Create compiler_time_file in advance.
	ofstream compiler_time_file_create;
	compiler_time_file_create.open (compiler_time_file.c_str());
	compiler_time_file_create << "";
	compiler_time_file_create.close();
	       	
	//Create exec_time_file in advance.
	ofstream exec_time_file_create;
	exec_time_file_create.open (runtime_file.c_str());
	exec_time_file_create << "";
	exec_time_file_create.close();
	
	//Create momery_time_file in advance.
	ofstream momery_time_file;
	momery_time_file.open (momery_file.c_str());
	momery_time_file << "";
	momery_time_file.close();
	
	
    
	int stat;	
	switch (get_file_attribute(filename))
	{
		case C_FILE:		//C_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, c file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			//It's important,after fork() child process copy the pather process's stdin stdout buffer ,so flush it ,or will see the duplicate of cout.
			cout.flush();
			pid_c = fork();
			if (pid_c != 0)
			{
				(void) signal(SIGALRM,ding);
				pause();
				usleep(CFILERUNTIME);
				int killresult;
				killresult = kill(pid_c, SIGTERM);
				handle_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_c  << endl;
				// wait() and waitpid()  ,just handle the child exit single SIGCHLD ,avoid zombie processes .
				//And the parent process recycle the PCB                       -- alex  01.03,2010
				wait(&stat);
			}
			if (pid_c == 0)
			{
				file_type = C_FILE;
			}
			break;	
			
		case CPP_FILE:		//CPP_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, c++ file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_cpp = fork();
			cout << filename << ":" 
				 << "The cpp_process pid:" << pid_cpp << endl;
			if (pid_cpp != 0)
			{
				(void) signal(SIGALRM,ding);
 				pause();
				cout << "father: get the child compiler finish signal ." << endl;
				//usleep(CPPFILERUNTIME);
				//int killresult = kill(pid_cpp,SIGTERM);
				//handle_timeout(filename);
				//if (killresult == 0)
				// cout << filename << ":"
				//   << "parent:success send the kill single to the child process!" << pid_cpp << '\n' << endl;
				// wait() and waitpid()  ,just handle the child exit single SIGCHLD ,avoid zombie processes .  0103,2010
				// 2011.04 let the child process control the time out self. 
				wait(&stat);
				cout << "father: get the child exit signal." << endl;
			}
			if (pid_cpp == 0)
			{
				file_type = CPP_FILE;
			}
			break;
			
		case PYTHON_FILE:		//PYTHON_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, python file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';

			cout.flush();	
 			pid_python = fork();
			if (pid_python != 0)
			{
				usleep(PYTHONFILERUNTIME);
				int killresult = kill(pid_python, SIGTERM);
				handle_python_timeout(filename);
				if (killresult == 0)
					cout << filename << ":" 
						 << "parent:success send the kill single to the child process!" << pid_python <<  endl;
				wait(&stat);
			}
 			if (pid_python == 0)
 			{
				file_type = PYTHON_FILE;
			}
			break;
			
		case HASKELL_FILE:		//HASKELL_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, haskell file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_haskell = fork();
			if (pid_haskell != 0)
			{
				(void) signal(SIGALRM, ding);
				pause();
				usleep(HASKELLFILERUNTIME);
				int killresult;
				killresult = kill(pid_haskell, SIGTERM);
				handle_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_haskell  << endl;
				wait(&stat);
			}
			if (pid_haskell == 0)
			{
				file_type = HASKELL_FILE;
			}
			break;
			
		case PROLOG_FILE:		//PROLOG_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, prolog file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_prolog = fork();
			if (pid_prolog != 0)
			{
				usleep(PROLOGFILERUNTIME);
				int killresult;
				killresult = kill(pid_prolog, SIGTERM);
				handle_prolog_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_prolog  << endl;    
				wait(&stat);
			}
			if (pid_prolog == 0)
			{
				file_type = PROLOG_FILE;
			}
			break;
			
		case LUA_FILE:		//LUA_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, lua file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_lua = fork();
			if (pid_lua != 0)
			{
				usleep(LUAFILERUNTIME);
				int killresult;
				killresult=kill(pid_lua, SIGTERM);
				handle_lua_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_lua << endl;                          
				wait(&stat);
			}
			if (pid_lua == 0)
			{
				file_type = LUA_FILE;
			}
			break;
			
		case JAVA_FILE:		//JAVA_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, java file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_java = fork();
			if (pid_java != 0)
			{
				(void) signal(SIGALRM, ding);
				pause();
				usleep(JAVAFILERUNTIME);
				int killresult;
				killresult = kill(pid_java, SIGTERM);
				handle_java_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_java << endl;                          
				wait(&stat);
			}
			if (pid_java == 0)
			{
				file_type = JAVA_FILE;
			}
			break;
			
		case GO_FILE:		//GO_FILE
			cout << filename
				 << ":"
				 << "after parser filetype, go file in the queue" << '\n';
			cout << filename << ":" 
				 << "fork process to compiler or interpert the code." << '\n';
			cout.flush();
			pid_go = fork();
			if (pid_go != 0)
			{
				(void) signal(SIGALRM, ding);
				pause();
				usleep(JAVAFILERUNTIME);
				int killresult;
				killresult = kill(pid_go, SIGTERM);
				handle_timeout(filename);
				if (killresult == 0)
					cout << filename << ":"
						 << "parent:success send the kill single to the child !" << pid_java << endl;                          
				wait(&stat);
			}
			if (pid_go == 0)
			{
				file_type = GO_FILE;
			}
			break;
			
		default:
			cout << filename << ":"
				 << "Unknow file type!" << endl;
			break;
	}


	
	//Process the c file!
	if (file_type == C_FILE)
	{
		cout << filename << ":"
			 << "child:Check the c file! " << '\n';
		handlewrong checkwrong;
		if (checkwrong.handlewrongfunction(filename) == 1)
		{
			cout << filename << ":"
				 << "child:the file can't pass the censor \n";
			
			ofstream myfile1;
			myfile1.open ( illegal_wrong_file.c_str());
			myfile1<<"Illegal code!";
			myfile1.close();
			
			//need a little time to wait the parent process be in the pause() stat! Or will be cause parent pause foreware!!!
			usleep(100000);
			kill(getppid(),SIGALRM);
			usleep(100000);
			exit (EXIT_SUCCESS);
		}
		
		string command;
		command.append("gcc -fopenmp  -O -fmessage-length=0 -fno-merge-constants  \
							-fstrict-aliasing -fstack-protector-all /var/www/exec/");
		command += filename;
		command.append("   -o   ");
		//Set the exec_file to the exec file after compiler.
		string exec_file;
		exec_file.append("/var/www/exec/exec.");
		exec_file.append(std::string(*(argv + 1)));
		command.append( exec_file   ) ;
		command.append(" > ");
		command += compiler_interpret_wrong_file;
		command.append(" 2>&1");

		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd, command.c_str());   //convert string to char*
	
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st,NULL);
		system(cmd);
		//if the compile over !let parent process go ahead!
		kill(getppid(), SIGALRM);
		gettimeofday(&et, NULL);                                                     //the file stream until the file end ,then Continued read the
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
		timeuse /= 1000000;
		
		ofstream myfile;
		myfile.open (compiler_time_file.c_str() );
		myfile<<"Compile Time:"<<timeuse <<"s";
		myfile.close();
		delete[] cmd;                               //Release  Dynamic Memory
		//execl("/usr/bin/gcc", "/usr/bin/gcc", "-o  ",  1260975782.79.c);
		
		cout << filename << ":"
			 << "child:the compile process are finished !,Now beginning to exec process"<<'\n';
		
		ifstream checkexecfile (exec_file.c_str() , ios::out  | ios::binary);
		if (checkexecfile.is_open())
		{
			checkexecfile.close();
			gettimeofday(&st, NULL);
			
			string exec_string;
			exec_string.append(exec_file);
			exec_string.append("  <  ");
			exec_string.append(stdin_file);
			exec_string.append("  >  ");
			exec_string.append(out_file);
			exec_string.append(" 2>&1");
			system(exec_string.c_str());
			
			gettimeofday(&et, NULL);                                                     //the file stream until the file end ,then Continued read the
			timeuse=1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
			timeuse/=1000000;
			
			ofstream myfile1;
			myfile1.open (runtime_file.c_str());
			myfile1<<"Execute Time:"<<timeuse <<"s";
			myfile1.close();
			
			cout << filename << ":"
				 << "child:  exec process are finished ,now wating foe child process return" << '\n';

		}
		else
		{
			cout << filename << ":"
				 << "child:the exec  file doesn't exist !\n"
				 << "now wating for child process return"
				 << endl;
			checkexecfile.close();
		}

	}
		
		
		
	//Process the c++ file!
	else if (file_type == CPP_FILE)
	{
		cout << filename << ":"
			 << "child:Check the c++ file! " << '\n';
			 
		//simply keywords filter.
		handlewrong checkwrong;
		if (checkwrong.handlewrongfunction(filename) == 1)
		{
			cout << filename << ":"
				 << "child:the file can't passing the censor \n";
			
			ofstream myfile1;
			myfile1.open ( illegal_wrong_file.c_str());
			myfile1<<"Illegal code!";
			myfile1.close();
			
			//need a little time to wait the parent process be in the pause() stat! Or will be cause parent pause foreware!!!
			usleep(100000);
			kill(getppid(),SIGALRM);
			usleep(100000);
			exit (EXIT_SUCCESS);
		}
		else
		{
			cout << filename << ":"
			     << "User code pass the simply keywords filter step!"
				 << endl;
		}
		
		//The compiler step.
		cout << filename << ":"
			 << "child:start the compile process " << '\n';
		string command;
		command.append("g++ -fopenmp     -std=c++98 -pedantic-errors -Wfatal-errors -Werror -Wall -Wextra -Wno-missing-field-initializers  \
							-Wwrite-strings -Wno-deprecated -Wno-unused -Wno-non-virtual-dtor -Wno-variadic-macros   \
							-fmessage-length=0 -ftemplate-depth-128 -fno-merge-constants -fno-nonansi-builtins   \
							-fno-gnu-keywords -fno-elide-constructors -fstrict-aliasing -fstack-protector-all -Winvalid-pch   \
							/var/www/exec/");
		command += filename;
		command.append("  -o   ");
		
		//Set the exec_file to the exec file after compiler.
		string exec_file;
		exec_file.append("/var/www/exec/exec.");
		exec_file.append(std::string(*(argv + 1)));
		command.append( exec_file   ) ;
		command.append(" > ");
		command += compiler_interpret_wrong_file;
		command.append(" 2>&1");
		
		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd,command.c_str());                //convert string to char*
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st,NULL);
		system(cmd);
		//if the compile over !let parent process go ahead!
		//there is a problem,i don't know if the compile process could be deadloop or not?Now i just hope compile process would't be deadlock!!!
		kill(getppid(), SIGALRM);
		gettimeofday(&et, NULL);                                                     //the file stream until the file end ,then Continued read the
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
		timeuse /= 1000000;
		cout << "Compile Time:" << timeuse  << "s" << endl;
		
		ofstream myfile;
		myfile.open (compiler_time_file.c_str() );
		myfile << "Compile Time:" << timeuse  << "s";
		myfile.close();
		delete[] cmd;                               //Release  Dynamic Memory

		cout << filename << ":"
			 << "child:the compile process are finished !,Now beginning to exec process" << '\n';

		//The exec code step.
		ifstream checkexecfile (exec_file.c_str() , ios::out  | ios::binary);

		if (checkexecfile.is_open())
		{
			checkexecfile.close();
			
			pid_t child;
			long orig_eax;
			struct rlimit r;
			child = fork();
			cout << "Fork child process to execve() the exec code, child pid="
			     << child << endl;
			int val;
			int flag = 0;
			
			gettimeofday(&st, NULL);
			
			if (child == 0) 
			{
				/**
				 * Rescource Limit .
				 * CPU Time: 1 s
				 * virtual memory: 50 M
				 */
				cout << "Set the child process resource limit." << endl;
				r.rlim_cur=1;  //1s
				r.rlim_max=2;  //2s
				if (setrlimit(RLIMIT_CPU, &r) < 0)
				{
					fprintf(stderr, "setrlimit error\n");
					//exit(1);
				}
				r.rlim_cur=50000000;  //bytes
				r.rlim_max=100000000;
				if (setrlimit(RLIMIT_AS, &r)<0)
				{
					fprintf(stderr,"setrlimit error\n");
					//exit(1);
				}

				
				if (getrlimit(RLIMIT_CPU, &r) < 0)
				{
					fprintf(stderr, "getrlimit error\n");
					//exit(1);
				}
				if (r.rlim_cur == RLIM_INFINITY )
					printf("RLIMIT_CPU.rlim_cur: no limit on resource.\n");
				else
					printf("RLIMIT_CPU.rlim_cur:%ld\n",r.rlim_cur);
				if (r.rlim_max == RLIM_INFINITY)
					printf("RLIMIT_CPU.rlim_max: no limit on resource.\n");
				else
					printf("RLIMIT_CPU.rlim_max:%ld\n",r.rlim_max);
					
				 /** get value of set **/
				 if(getrlimit(RLIMIT_AS, &r)<0)
				 {
					 fprintf(stderr,"getrlimit error\n");
					 //exit(1);
				 }
				 printf("RLIMIT_AS_cur:%ld\n",r.rlim_cur);
				 printf("RLIMIT_AS_max:%ld\n",r.rlim_max);
			
				char* cmd_exec = new char [exec_file.size() + 1];           //apply the Dynamic Memory
				strcpy(cmd_exec, exec_file.c_str());   //convert string to const char*,then copy it to char*
				cout << "Exec command :" << cmd_exec << endl;
				
				freopen (out_file.c_str(), "w", stdout);          //Reopen stream with different file or mode
				freopen (stdin_file.c_str(), "r", stdin);
				
				char *prog[] = {cmd_exec, NULL};
			        char *env[] = {(char*)"USER=alex", (char*)"PATH=/var/www/exec", NULL};
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				
				//A child process created via fork(2) inherits its parents resource limits. 
				//Resource limits are preserved across execve(2). That's important.
				execve(prog[0], prog, env);
				
				//execve () cann't copy the code below the execve() call,so how to deal with the following step?
				//(That means how to delete cmd_exec data space?) 2011.04.07
				//actually ,when execve() calling ,the original process data space will be released automatic. 2011.04.08
				delete cmd_exec;
				fclose (stdin);
				fclose (stdout);
				//system(exec_string.c_str());
														//this makes the stdin (cin),from the standard I/O
														//terminoal to the file (stdin),the can realize the
														//Redirection stdin,the essence of stdin just a file pointer.it abstract the I/o Console to a file .
														//every thing just a file in *nix.
				
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
					{
					    // Use this way just get the real time (Real is wall clock time - time from start to finish of the call. 
						// This is all elapsed time including time slices used by other processes and time the process spends 
						// blocked (for example if it is waiting for I/O to complete). )
						gettimeofday(&et, NULL);
						timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;
						timeuse /= 1000;
						cout << "Exec Real Time:" << timeuse << "ms" << endl;
						
						/*time measure ,get the CPU time (user + sys) of exec process (child process of this process)
						struct tms {
						clock_t tms_utime;  // user time 
						clock_t tms_stime;  // system time 
						clock_t tms_cutime; // user time of children 
						clock_t tms_cstime; // system time of children 
						} ;    
						user : user cpu time 
						sys : system cput time
											2011.04.08
						*/
						struct tms measure_time;
						times (&measure_time);
						clock_t child_cpu_time;
						child_cpu_time = measure_time.tms_cutime + measure_time.tms_cstime;
						cout << "Exec CPU Time:" << child_cpu_time << "ms" << endl;
						
						
						ofstream myfile1;
						myfile1.open (runtime_file.c_str());
						myfile1 << "Execute Time:" << child_cpu_time << "ms";
						myfile1.close();
						
						printf("child: exec process are finished ,now wating for child process return\n");
						return 0; 
					}
					if(flag == 0) //get the signals for child process call a syscall.
					{ 
						orig_eax = ptrace(PTRACE_PEEKUSER, child, ORIG_EAX*4, NULL); 
						//printf("Process executed system call ID = %ld ",orig_eax); 
						if (orig_eax == -1)       //Reach the resource limit cpu time. 
						{
							printf("Time OUT of resource limit,the child process killed by the kernel!\n");
							return 0;
						}
						string block_syscall = check_syscalls(orig_eax) ;
						if (block_syscall != "")  
						{
							
							//printf("Process executed system call ID = %ld ,__NR_nanosleep child process be killed\n ",orig_eax); 
							cout << "Block Type :" 
							     << block_syscall
								 << endl;
							ofstream illegal_file;
							illegal_file.open (illegal_wrong_file.c_str());
							illegal_file << "Disallowed system call: "
							           << block_syscall;
							illegal_file.close();	 
							
							kill(child, SIGTERM);
							return 0; 
						}
						if (orig_eax == 252)  //__NR_exit_group, before child process exit ,get the virtual memory.
						{
							printf("catch the __NR_exit_group syscall=%ld\n", orig_eax);
							char path_name[30];
							char path[10] = "/proc/";
							char pid_buf[10];
							snprintf(pid_buf, 10, "%d", child);
							strcpy (path_name, path);
							strcat (path_name, pid_buf);
							strcat (path_name, "/status");
							cout << "Exec process path_name:" << path_name << endl;
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
										
										// Write the exec memory to the memory_file.
										ofstream memoryfile;
										memoryfile.open (momery_file.c_str());
										memoryfile << tmp;
										memoryfile.close();
										
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
						
						flag = 1; 
					} 
					else    //get the signals for child process exit a syscall.
					{ 
						orig_eax = ptrace(PTRACE_PEEKUSER, child, EAX*4, NULL); 
						//printf("with return value= %ld\n", orig_eax); 
						flag = 0; 
					} 
					ptrace(PTRACE_SYSCALL,child,NULL,NULL); 
				}
			}
			

		}
		else
		{
			cout << filename << ":"
				 << "child:the exec  file doesn't exist !\n"
				 << "now wating for child process return"
				 << endl;
			checkexecfile.close();
		}
	}
		
	//Process the python file!
	else if (file_type == PYTHON_FILE)
	{
		cout << filename << ":"
			 << "child:start the python file check. "<<'\n';
		handlewrong  checkwrong;
		if(checkwrong.handlepython(filename) == 1)
		{
			cout << filename << ":"
				 <<"child:the file can't pass the censor \n";
			ofstream myfile1;
			myfile1.open ( illegal_wrong_file.c_str());
			myfile1<<"Illegal code!";
			myfile1.close();
			exit ( EXIT_FAILURE);
		}
		
		string command;
		command.append("python   /var/www/exec/");
		command += filename;
		command.append("   <    ");
		command.append(stdin_file);
		command.append("   >    ");
		command.append(out_file);
		command.append("  2>&1"  );
		
		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd,command.c_str());                //convert string to char*
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st, NULL);
		system(cmd);
		gettimeofday(&et, NULL);
		delete[] cmd;                               //Release  Dynamic Memory
		
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;
		timeuse /= 1000000;

		ofstream myfile1;
		myfile1.open (runtime_file.c_str());
		myfile1 << "Execute Time:" << timeuse << "s";

		myfile1.close();

	}
	
	//Process the haskell file!
	else if (file_type == HASKELL_FILE)
	{
		cout << filename << ":"
			 << "child:Process the haskell file! " << '\n';
		string command;
		command.append("ghc  /var/www/exec/");
		command += filename;
		command.append("   -o   ");
		
		string exec_file;
		exec_file.append("/var/www/exec/exec.");
		exec_file.append(std::string(*(argv + 1)));
		command.append( exec_file   ) ;
		
		command.append(" > ");
		command += compiler_interpret_wrong_file;
		command.append(" 2>&1");

		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd, command.c_str());   //convert string to char*
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st, NULL);
		system(cmd);
		delete [] cmd;
		kill(getppid(),SIGALRM);
		gettimeofday(&et,NULL);
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
		timeuse /= 1000000;
		ofstream myfile;
		myfile.open (compiler_time_file.c_str() );
		myfile<<"Compile Time:"<<timeuse <<"s";
		myfile.close();
		
		cout << filename << ":"
			 <<"child:the compile process are finished !,Now beginning to exec process"<<'\n';
		ifstream checkexecfile (exec_file.c_str() , ios::out  | ios::binary);
		if (checkexecfile.is_open())
		{
			checkexecfile.close();
			gettimeofday(&st, NULL);
			string exec_string;
			exec_string.append(exec_file);
			exec_string.append("  <  ");
			exec_string.append(stdin_file);
			exec_string.append("  >  ");
			exec_string.append(out_file);
			exec_string.append(" 2>&1");
			system(exec_string.c_str());
			gettimeofday(&et,NULL);                                                     //the file stream until the file end ,then Continued read the
			timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
			timeuse /= 1000000;
			
			ofstream myfile1;
			myfile1.open (runtime_file.c_str());
			myfile1 << "Execute Time:"<< timeuse << "s";
			myfile1.close();
			cout << filename << ":"
				 <<"child:  exec process are finished ,now wating foe child process return"<<'\n';

		}
		else
		{
			cout << filename << ":"
				 << "child:the exec  file doesn't exist !\n"
				 << "now wating for child process return"
				 << endl;
			checkexecfile.close();
		}
	}

	//Process the prolog file!
	else if (file_type == PROLOG_FILE)
	{
		cout << filename << ":"
			 << "child:Process the prolog file! " << '\n';
		
		string command;
		command.append("swipl -f  /var/www/exec/");
		command += filename;
		command.append("   -q   ");
		command.append("   <    ");
		command.append(stdin_file);
		command.append("   >    ");
		command.append(out_file);
		command.append("  2>&1"  );
		
		char* cmd = new char [command.size()+1];
		strcpy(cmd,command.c_str());
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st, NULL);
		system(cmd);
		gettimeofday(&et, NULL);
		delete[] cmd;
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;
		timeuse /= 1000000;
		
		ofstream myfile1;
		myfile1.open (runtime_file.c_str());
		myfile1 << "Execute Time:" << timeuse << "s";

		myfile1.close();
	}
	
	//Process the lua file!
	else if (file_type == LUA_FILE)
	{
		cout << filename << ":"
			 << "child:Process the lua file! " << '\n';
	   
		string command;
		command.append("lua   /var/www/exec/");
		command += filename;
		command.append("   -q   ");
		command.append("   <    ");
		command.append(stdin_file);
		command.append("   >    ");
		command.append(out_file);
		command.append("  2>&1"  );
		
		char* cmd = new char [command.size()+1];
		strcpy(cmd, command.c_str());
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st, NULL);
		system(cmd);
		gettimeofday(&et, NULL);
		delete[] cmd;
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;
		timeuse /= 1000000;
		
		ofstream myfile1;
		myfile1.open (runtime_file.c_str());
		myfile1 << "Execute Time:" << timeuse << "s";

		myfile1.close();

	}

	//Process the java file!
	else if (file_type == JAVA_FILE)
	{
		
		cout << filename << ":"
			 << "child:Process the java file! " << '\n';
			  
		/**
		 * Java public class name must be consistently with 
		 * .Java file's name. So make a copy of java file to 
		 * fit the Java's features.
		 */
		string old_java_file = "/var/www/exec/";
		string new_java_file;
		string check_public_keywords;
		old_java_file += filename;
		int mark_loc;
		ifstream java_file (old_java_file.c_str());
		if (java_file.is_open())
		{
			while (! java_file.eof() )
			{
				getline (java_file, check_public_keywords);
				if ( (mark_loc = check_public_keywords.find("public")) != -1)
				{
					cout << "Find public keyword in:" << check_public_keywords << "Size:" << check_public_keywords.size() << endl;	
					mark_loc += 6;
					while (check_public_keywords[mark_loc] == ' ')
					{
						mark_loc++;
					}
					//cout << "Filter the black space\n";
					if (check_public_keywords.compare(mark_loc, 5, "class") == 0) 
					{
						//cout << "find the class keywords\n";
						mark_loc += 5;
						int tmp_mark;
						while (check_public_keywords[mark_loc] == ' ')
						{
							//cout << mark_loc << endl;
							mark_loc++;
						}
						tmp_mark = mark_loc;
						//cout << mark_loc << endl;
						/**
						 * About Line Endings differents from every platforms,
						 * Windows CRLF . Linux LF(Line Feed,New Line) . Mac CR(Carriage Return)
						 * CRLF --->  "\r\n"
						 * LF ---> 10 '\n'
						 * CR --> 13  '\r'
						 */
						while ((check_public_keywords[tmp_mark] != 13 )&& (check_public_keywords[tmp_mark] != ' ' )&& (check_public_keywords[tmp_mark] != '{') && (check_public_keywords[tmp_mark] != 10) )
						{
							cout << tmp_mark << " " << check_public_keywords[tmp_mark] << endl;
							tmp_mark++;
						}
						new_java_file = check_public_keywords.substr(mark_loc, tmp_mark - mark_loc);
						cout << "Get the java public class name: " << new_java_file << "  Size:" << new_java_file.size() <<  endl;
						java_file.close();
						break;
					}
					
				}
			}
		}
		else
		{
		    cout << "Can't open the java file to analysis." << endl;
		}
		// Copy the old java file to the new java file .
		char buffer[10];
		int fd_new, fd_old;
		int off_size_file;
		new_java_file = new_java_file + ".java";
		new_java_file = "/var/www/exec/" + new_java_file;
		cout << "New java file: " << new_java_file << endl;
		if ( (fd_old = open(old_java_file.c_str(), O_RDONLY)) <0)
		{
			cout << "Open the old java file error." << endl;
		}	
		if ( (fd_new = creat(new_java_file.c_str(), O_RDWR|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) < 0)
		{
			cout << "Creat the new java file error." << endl;
		}	
		else
		{
			while ( (off_size_file = read(fd_old, buffer, 10)) > 0)
			{
				if ( write(fd_new, buffer, off_size_file) != off_size_file )
				{
					cout << "Write the new java file error." << endl;
				}
			}
			cout << "Copy the old java file to new java file succeed." << endl;
		}
		close (fd_new);
		close (fd_old);

	/**
	 * Compielr java file to class file.
	 */	
		string command;
		//command.append("javac  /var/www/exec/");
		// command += filename;
		command.append("javac ");
		command += new_java_file;
		command.append(" > ");
		command += compiler_interpret_wrong_file;
		command.append(" 2>&1");

		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd, command.c_str());   //convert string to char*
		
		struct timeval st, et;
		float timeuse;
		
		gettimeofday(&st, NULL);
		// COmpile command.
		system(cmd);
		delete [] cmd;
		//Send the signal to father process ,the compile is done.
		kill(getppid(),SIGALRM);
		
		/**
		 * Get the java class name.
		 */
		DIR *d;
		struct dirent *dent;
		char path[255], tmp[255];
		//getcwd(path, sizeof(path));
		strcpy(path, "/var/www/exec/");
		/* Attempt to open the directory. */
		if (!(d = opendir(path)))
		{
			cout << "file to open " << path << endl;
			//return 0;
		}
		string exec_file_full;
		string exec_file;
		/* Read directory. */
		while ((dent = readdir(d)))
		{
			//cout << dent->d_name << endl;
			strcpy(tmp, dent->d_name);
			exec_file_full = tmp;
			size_t pos;
			int is_find_main_class = 0;
			if ( (pos = exec_file_full.find(".class")) != string::npos)
			{
				cout << "Find the java class file:" << exec_file_full << endl;
				exec_file = exec_file_full.substr(0, pos);
				cout << "Get the java class:" << exec_file << endl;
				exec_file_full = "/var/www/exec/" + exec_file_full;
				ifstream java_main_class (exec_file_full.c_str());
				string readline;
				if (java_main_class.is_open())
				{
					while (! java_main_class.eof() )
					{
						getline (java_main_class, readline);
						if (readline.find("main") != -1)
						{
							cout << "Find the main-class: " << exec_file_full << endl;
							is_find_main_class = 1;
							break;
						}
					}
				}
				else
				{
					cout << "Can't open " << exec_file_full << endl;
				}
				
			}	
			if ( is_find_main_class )
			{
				break;
			}
		}
		string java_class_file_full;
		//java_class_file_full.append("/var/www/exec/");
		java_class_file_full = exec_file_full;
		//string java_class_file;
		//java_class_file.append("/var/www/exec/");
		//java_class_file += exec_file;
		/* Close it. */
		closedir(d);

		/**
		 * Execute the java class .
		 */
		gettimeofday(&et,NULL);
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
		timeuse /= 1000000;
		ofstream myfile;
		myfile.open (compiler_time_file.c_str() );
		myfile<<"Compile Time:"<<timeuse <<"s";
		myfile.close();
		
		cout << filename << ":"
			 <<"child:the compile process are finished !,Now beginning to exec process"<<'\n';
		ifstream checkexecfile (java_class_file_full.c_str() , ios::out  | ios::binary);
		if (checkexecfile.is_open())
		{
			checkexecfile.close();
			gettimeofday(&st, NULL);
			string exec_string;
			exec_string.append("java -classpath \"/var/www/exec\" ");
			exec_string.append(exec_file);
			exec_string.append("  <  ");
			exec_string.append(stdin_file);
			exec_string.append("  >  ");
			exec_string.append(out_file);
			exec_string.append(" 2>&1");
			system(exec_string.c_str());
			gettimeofday(&et,NULL);                                                     //the file stream until the file end ,then Continued read the
			timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
			timeuse /= 1000000;
			
			ofstream myfile1;
			myfile1.open (runtime_file.c_str());
			myfile1 << "Execute Time:"<< timeuse << "s";
			myfile1.close();
			cout << filename << ":"
				 <<"child:  exec process are finished ,now wating foe child process return"<<'\n';
							 
		    /**
			 * Remove the java class file.
			 */
			d = opendir(path);
			
			while ((dent = readdir(d)))
			{
				//cout << dent->d_name << endl;
				strcpy(tmp, dent->d_name);
				exec_file_full = tmp;
				if ( exec_file_full.find(".class") != string::npos)
				{
					
					string remove_class_file;
					remove_class_file.append("/var/www/exec/");
					remove_class_file += exec_file_full;
					if (remove(remove_class_file.c_str()) == 0)
					{
						cout << "Remove file:" << remove_class_file << " successfully." << endl;
					}
					else
					{
						cout << "Remove file:" << remove_class_file << " unsuccessfully." << endl;
					}
				}
            }
			
			closedir(d);

		}
		else
		{
			cout << filename << ":"
				 << "child:the exec  file doesn't exist !\n"
				 << "now wating for child process return"
				 << endl;
			checkexecfile.close();
		}
	}
	
	//Process the go file!
	else if (file_type == GO_FILE)
	{
		cout << filename << ":"
			 << "child:Process the go file! " << '\n';
			 
		if (chdir("/var/www/exec") < 0)
		{
			cout << "Failed to change the directory ." << endl; 
		}
		
		/**
		 * COmpiler the go file.
		 * The compiler of go is different by the machine .
		 * 6g is the Go compiler for amd64; it will write the output in file.6. 
		 * The ¡®6¡¯ identifies files for the amd64 architecture. 
		 * The identifier letters for 386 and arm are ¡®8¡¯ and ¡®5¡¯. 
		 * That is, if you were compiling for 386, you would use 8g and the output would be named file.8.
		 * My dev machine is 386 , i choice the 8g,8l .
		 */
		string command;
		command.append("/var/www/go/bin/8g  /var/www/exec/");
		command += filename;
		command.append(" > ");
		command += compiler_interpret_wrong_file;
		command.append(" 2>&1");
		cout << "Compiler command: " 
			 << command
			 << endl;
		char* cmd = new char [command.size()+1];           //apply the Dynamic Memory
		strcpy(cmd, command.c_str());   //convert string to char*
		struct timeval st, et;
		float timeuse;
		gettimeofday(&st, NULL);
		system(cmd);
		delete [] cmd;
		
		/**
		 * Link the go file.
		 */
		string link_file_name;
		size_t dot_pos;
		dot_pos = filename.find(".go");
		link_file_name = filename.substr(0, dot_pos);
		link_file_name += ".8";
		string link_command;
		link_command = "/var/www/go/bin/8l -o ";
		string exec_file;
		exec_file.append("/var/www/exec/exec.");
		exec_file.append(std::string(*(argv + 1)));
		link_command.append( exec_file ) ;
		link_command += " ";
		link_command += link_file_name;
		link_command += " >> ";
		link_command += compiler_interpret_wrong_file;
		link_command += " 2>&1";
		cout << "Link command: "
			 << link_command
			 << endl;
		system(link_command.c_str());
		
		kill(getppid(), SIGALRM);
		gettimeofday(&et, NULL);
		timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
		timeuse /= 1000000;
		ofstream myfile;
		myfile.open (compiler_time_file.c_str() );
		myfile << "Compile Time:" << timeuse << "s";
		myfile.close();
		
		/**
		 * Execute the go file.
		 */
		cout << filename << ":"
			 <<"child:the compile process are finished !,Now beginning to exec process"<<'\n';
		 
		if ( access(exec_file.c_str(), R_OK) == 0)
		{

			gettimeofday(&st, NULL);
			string exec_string;
			exec_string.append(exec_file);
			exec_string.append("  <  ");
			exec_string.append(stdin_file);
			exec_string.append("  >  ");
			exec_string.append(out_file);
			exec_string.append(" 2>&1");
			system(exec_string.c_str());
			gettimeofday(&et,NULL);                                                     //the file stream until the file end ,then Continued read the
			timeuse = 1000000*(et.tv_sec-st.tv_sec) + et.tv_usec-st.tv_usec;          //last number to the cin flow !!!great!
			timeuse /= 1000000;
			
			ofstream myfile1;
			myfile1.open (runtime_file.c_str());
			myfile1 << "Execute Time:"<< timeuse << "s";
			myfile1.close();
			cout << filename << ":"
				 <<"child:  exec process are finished ,now wating foe child process return"<<'\n';

		}
		else
		{
			cout << filename << ":"
				 << "child:the exec file doesn't exist !\n"
				 << "now wating for child process return"
				 << endl;
			 
		}
	}

//Child process exit!
	if (file_type != 0)
	{   
	cout << filename << ":"
		 << "child:All tasks finished. "
		 << " The file_name is:"
		 << filename
		 << endl;

	exit(EXIT_SUCCESS);
	}

//Father process exit!
	else
	{
		cout << filename << ":"
			 << "parent:All tasks finished! "
			 << endl;
		return 0;
	}
}


void handle_timeout(string exec_name)
{
	int killsystemthread;
	string killsysthraed;
	//just have a bug ,if another process in some tty name exec ,just also be killed!!!
	string command;
	command.append("ps -a |grep   exec.");
	command += exec_name;
	command.append("  >  ");
	string systemthread_file;
	systemthread_file.append("/var/www/output/systemthread.");
	systemthread_file += exec_name;
	command += systemthread_file;
	system(command.c_str());
	//system("ps -a |grep   exec  > /var/www/output/systemthread");
	ifstream killsysthreadfile(systemthread_file.c_str());
	if (killsysthreadfile.is_open())
	{
		killsysthreadfile >> killsysthraed;
		if(killsysthraed.size()!=0)
		{
			killsystemthread = boost::lexical_cast<int>(killsysthraed);       //thanks the boost lexical_cast function!it's great
			kill(killsystemthread,SIGTERM);
			//another way !
			//system("killall exec");
			cout << filename << ":"
							 << "parent:kill the exec subthread ,for it's timeout !\n"<<endl;
			cout << filename << ":"
							 <<"parent:success kill the exec,reach the time limit , the exec pid is :"<<killsystemthread<<endl;
		}
	}
	killsysthreadfile.close();
}

//another bug ,if another python process executing ,will be wrong !
void handle_python_timeout(string exec_name)
{
	int killsystemthread;
	string killsysthraed;
	string command;
	command.append("ps -a |grep   python  >");
	string systemthread_file;
	systemthread_file.append("/var/www/output/systemthread.");
	systemthread_file += exec_name;
	command += systemthread_file;
	system(command.c_str());
	
	ifstream killsysthreadfile(systemthread_file.c_str());
	if (killsysthreadfile.is_open())
	{
		killsysthreadfile >> killsysthraed;
		if (killsysthraed.size() != 0)
		{
			killsystemthread = boost::lexical_cast<int>(killsysthraed);       //thanks the boost lexical_cast function!it's great
			kill(killsystemthread,SIGTERM);
			cout << filename << ":"
							 <<"parent:kill the exec subthread ,for it's timeout !\n"<<endl;
			cout << filename << ":"
							 <<"parent:success kill the exec,reach the time limit , the exec pid is :"<<killsystemthread<<endl;
		}
	}
	killsysthreadfile.close();
}

//a problem ,if a process swipl under the go ,just will be killed !
void handle_prolog_timeout(string exec_name)
{
	int killsystemthread;
	string killsysthraed;
	string command;
	command.append("ps -a |grep   swipl  >");
	string systemthread_file;
	systemthread_file.append("/var/www/output/systemthread.");
	systemthread_file += exec_name;
	command += systemthread_file;
	system(command.c_str());
	
	ifstream killsysthreadfile(systemthread_file.c_str());
	if (killsysthreadfile.is_open())
	{
		killsysthreadfile >> killsysthraed;
		if (killsysthraed.size() != 0)
		{
			killsystemthread = boost::lexical_cast<int>(killsysthraed);       //thanks the boost lexical_cast function!it's great
			kill(killsystemthread,SIGTERM);
			cout << filename << ":"
							 <<"parent:kill the exec subthread ,for it's timeout !\n"<<endl;
			cout << filename << ":"
							 <<"parent:success kill the exec,reach the time limit , the exec pid is :"<<killsystemthread<<endl;
		}
	}
	killsysthreadfile.close();
}

void handle_lua_timeout(string exec_name)
{
	int killsystemthread;
	string killsysthraed;
	string command;
	command.append("ps -a |grep   lua  >");
	string systemthread_file;
	systemthread_file.append("/var/www/output/systemthread.");
	systemthread_file += exec_name;
	command += systemthread_file;
	system(command.c_str());
	
	ifstream killsysthreadfile(systemthread_file.c_str());
	if (killsysthreadfile.is_open())
	{
		killsysthreadfile >> killsysthraed;
		if (killsysthraed.size() != 0)
		{
			killsystemthread = boost::lexical_cast<int>(killsysthraed);       //thanks the boost lexical_cast function!it's great
			kill(killsystemthread,SIGTERM);
			cout << filename << ":"
							 <<"parent:kill the exec subthread ,for it's timeout !\n"<<endl;
			cout << filename << ":"
							 <<"parent:success kill the exec,reach the time limit , the exec pid is :"<<killsystemthread<<endl;
		}
	}
	killsysthreadfile.close();
}

void handle_java_timeout(string exec_name)
{
	int killsystemthread;
	string killsysthraed;
	string command;
	command.append("ps -a |grep   java  >");
	string systemthread_file;
	systemthread_file.append("/var/www/output/systemthread.");
	systemthread_file += exec_name;
	command += systemthread_file;
	system(command.c_str());
	
	ifstream killsysthreadfile(systemthread_file.c_str());
	if (killsysthreadfile.is_open())
	{
		killsysthreadfile >> killsysthraed;
		if (killsysthraed.size() != 0)
		{
			killsystemthread = boost::lexical_cast<int>(killsysthraed);       //thanks the boost lexical_cast function!it's great
			kill(killsystemthread,SIGTERM);
			cout << filename << ":"
							 <<"parent:kill the exec subthread ,for it's timeout !\n"<<endl;
			cout << filename << ":"
							 <<"parent:success kill the exec,reach the time limit , the exec pid is :"<<killsystemthread<<endl;
		}
	}
	killsysthreadfile.close();
}
