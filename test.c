
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	char cmd[] = "/usr/bin/ls";
	char *argvec[] = {"ls", "-l", NULL};
	char *envvec[] = {NULL};
	
	printf("%s\n", cmd);
	execve(cmd, argvec, envvec);
	return (0);
}