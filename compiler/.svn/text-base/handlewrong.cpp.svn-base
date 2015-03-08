/*
 * Copyright (C) 2010 Alex Zhang
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

#include "handlewrong.h"
#include <cstring>
int  handlewrong::handlewrongfunction(string &tmp)
{
        char* locationchar;
	string readline,location;
	location="/var/www/exec/";
	location+=tmp;
	locationchar = new char [location.size()+1];           //apply the Dynamic Memory
    strcpy(locationchar,location.c_str());   //convert string to char*
  	ifstream myfile (locationchar);
  	if (myfile.is_open())
  	{
  	  while (! myfile.eof() )
  	  {
  	      /*check the code keyword can be add below*/
  	      cout << tmp << ":"
                   << "analyse a line of source code! \n";cout.flush();
  	    getline (myfile,readline);
  	    if(readline.find("fork(")!=-1)
            return 1;
  	    if(readline.find("clone(")!=-1)
  	    	return 1;
  	    if(readline.find("sleep(")!=-1)
  	    	return 1;
  	    if(readline.find("wait(")!=-1)
  	    	return 1;
  	    if(readline.find("vfork(")!=-1)
  	    	return 1;
  	    if(readline.find("exec(")!=-1)
  	    	return 1;
  	    if(readline.find("kill(")!=-1)
  	    	return 1;
  	    if(readline.find("system(")!=-1)
  	    	return 1;
       if(readline.find("popen(")!=-1)
         return 1;

   	 }
  	  myfile.close();
  	}

 	 else
             cout << tmp << ":"
                  << "unable to open the file!"
                  << endl;
	return 0;
}

int  handlewrong::handlepython(string &tmp)
{
   char* locationchar;
	string readline,location;
	location="/var/www/exec/";
	location+=tmp;
	locationchar = new char [location.size()+1];           //apply the Dynamic Memory
    strcpy(locationchar,location.c_str());   //convert string to char*
  	ifstream myfile (locationchar);
  	if (myfile.is_open())
  	{
  	  while (! myfile.eof() )
  	  {
  	      /*check the code keyword can be add below*/
  	      cout << tmp << ":"
                   << "analyse the python code! \n";cout.flush();
  	    getline (myfile,readline);
  	    if(readline.find("import")!=-1)
  	    {
  	       if(readline.find("os")!=-1)
            return 1;
         if(readline.find("os")!=-1)
            return 1;
  	    }

      }
  	}
 	 else
 	  cout << tmp << ":"
               << "unable to open the file!";
	return 0;
}

/*      Notes */
/* the best way to check the code is use the strace ,it can analysis
  the code syscalls ,clone() execve() ,nanosleep() ,wait() ,vfork()
  but if the code has these syscalls ,strace check need start the code ,
  it is Contradictory!!!   */
