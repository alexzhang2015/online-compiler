#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <sys/wait.h>
#include <sys/file.h>
using namespace std;
int main()
{
ofstream myfile;
  myfile.open ("result");
flock(  myfile, LOCK_EX);

return 0;
}
