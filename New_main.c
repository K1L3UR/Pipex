#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "pipex.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

//cree un fichier av open then lire et envoyer le fichier

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	exec_pipe(char *env[])
{
	int	pid;
	int	pipefd[2];
	int	fd_in;
	int	i;
	int	nb_pipe;

	nb_pipe = 2;
	i = 0;
	fd_in = dup(STDIN_FILENO);
	while (i < nb_pipe)
	{
		pipe(pipefd);
		pid = fork();
		pipefd[1] = dup2(fd_in, STDIN_FILENO);
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if (i + 1 != nb_pipe)
				dup2(pipefd[1], STDOUT_FILENO);
			close(fd_in);
			close(pipefd[0]);
			close(pipefd[1]);
			//if (i == 0)
			//	execve(cmd, arvec, envec);
		}
		dup2(pipefd[0], fd_in);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	close(fd_in);
}

char	**extract_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	return (ft_split(env[i] + 5, ':' ));
}

char	*find_binaries(char **tab, char *bin_name)
{
	int		i;
	char	*s;

	i = 0;
	while (tab[i])
	{
		s = ft_strjoin3(tab[i], "/", bin_name);
		if (access(s, X_OK) == 0)
			return (s);
		i++;
		free(s);
	}
	return (NULL);
}

void	exec_commands(char **env, char **tab, char *argv)
{
	char	**avtab;
	int		i;
	char	*s;

	i = 0;
	//printf("argv = %s\n", argv);
	avtab = ft_split(argv, ' ');
	//print_tab(avtab);
	if (!(avtab))
		perror("ft_split");
	s = find_binaries(tab, *avtab);
	execve(s, avtab, env);
	perror("execve");
	free(s);
	exit(EXIT_FAILURE);
}

int	exec(char **env, char **argv, int argc, char **tab)
{
	int		pipefd[2];
	int		fd_in;
	int		i;
	int		nb_commands;

	nb_commands = argc - 3;
	i = 0;
	fd_in = dup(STDIN_FILENO);
	while (i < nb_commands)
	{
		pipe(pipefd);
		if (!(fork()))
		{
			if (i == 0)
			{
				fd_in = open(argv[1], O_RDONLY);
				if (fd_in == -1)
				{
					perror("ouveture fichier");
					exit(0);
				}
				dup2(fd_in, STDIN_FILENO);
			}
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != nb_commands)
				dup2(pipefd[1], STDOUT_FILENO);
			else
			{
				fd_in = open(argv[argc - 1], O_CREAT | O_WRONLY
				|O_TRUNC, 0644);
				dup2(fd_in, STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			close(fd_in);
			exec_commands(env, tab, argv[i + 2]);
		}
		dup2(pipefd[0], fd_in);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	close(fd_in);
	i = -1;
	while (++i < nb_commands)
		wait(NULL);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	char	**tab;
	int		i;

	i = 0;
	if (argc < 5)
		exit((printf("arg < 5"), 0));
	tab = extract_path(env);
	if (!(tab))
		return (0);
	exec(env, argv, argc, tab);
	return (0);
}
