#!/usr/local/bin/python

import string, sys ,os
#restart the  apache
os.system("sudo /etc/init.d/apache2 restart")
#empty the mutex file,
FILE=open("/var/www/submitlock","w")
FILE.write("") 
FILE.close()

FILE=open("/var/www/output/wrong","w")
FILE.write("") 
FILE.close()

FILE=open("/var/www//output/compilertime.txt","w")
FILE.write("") 
FILE.close()

FILE=open("/var/www//output/runtime.txt","w")
FILE.write("") 
FILE.close()

FILE=open("/var/www//output/stdin","w")
FILE.write("") 
FILE.close()

FILE=open("/var/www//output/out.txt","w")
FILE.write("") 
FILE.close()

raw_input("Press any Key to exit!")
