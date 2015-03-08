#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

using namespace std;

int main()
{
    DIR *d;
    struct dirent *dent;    
    char path[255], tmp[255];
    getcwd(path, sizeof(path));
    /* Attempt to open the directory. */
    if (!(d = opendir(path)))
    {
	cout << "file to open " << path << endl;
	return 0;
    }
    /* Read directory. */
    while ((dent = readdir(d)))
    {
        //cout << dent->d_name << endl;
        strcpy(tmp, dent->d_name);
        string file_name = tmp;
	size_t pos;
        if ((pos = file_name.find(".cpp")) != string::npos)
        {
   	    // pos = file_name.find(".cpp");
	     cout << file_name << endl;
	     cout << (int)pos << endl;
             string file_name_tmp = file_name.substr(0, pos);
             cout << file_name_tmp << endl;
             if (remove("test.cpp") == 0)
             {
		cout << "remove success!" << endl;
             }
        } 
    }
    /* Close it. */
    closedir(d);

    return 0;
}
