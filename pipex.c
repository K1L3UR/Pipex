#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int	pid;
	int	fd[1];

	if (argc < 2)
		exit(0);
	pid = fork();
	if (pid < 0)
		exit(1);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execlp("ls", "ls" "-la", NULL);
	waitpid(pid, NULL, 0);
	return (0);
}
