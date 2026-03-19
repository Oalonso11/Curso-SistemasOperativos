#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
int status;

execl("./bin/hello", NULL);
perror("excecl ha fallado.");
return 0;

}


