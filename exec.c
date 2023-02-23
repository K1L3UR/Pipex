/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <arnduran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:26:38 by arnduran          #+#    #+#             */
/*   Updated: 2023/02/23 02:09:35 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path(char **env)
{
	int	i;

	i = 0;
	if (!*env)
		return (ft_split("", '{'));
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	return (ft_split(env[i] + 5, ':' ));
}

char	*find_binaries(char **tab, char *bin_name)
{
	int		i;
	char	*s;

	i = -1;
	while (tab[++i])
	{
		if (ft_strchr(bin_name, '/'))
			return (bin_name);
		s = ft_strjoin3(tab[i], "/", bin_name);
		if (!s)
			return (NULL);
		if (access(s, X_OK) == 0)
			return (s);
		free(s);
	}
	return (bin_name);
}

int	open_file(char **argv)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error file opening");
		exit(0);
	}
	dup2(fd_in, STDIN_FILENO);
	return (fd_in);
}

void	child_management(char **argv, int *tab_norme, char **env, char **tab)
{
	int	pipefd[2];

	pipe(pipefd);
	if (!fork())
	{
		if (tab_norme[2] == 0)
			tab_norme[0] = open_file(argv);
		if (tab_norme[2] != 0)
			dup2(tab_norme[0], STDIN_FILENO);
		if ((tab_norme[2] + 1) != tab_norme[1])
			dup2(pipefd[1], STDOUT_FILENO);
		else
		{
			tab_norme[0] = open(argv[tab_norme[1] + 2], O_CREAT | O_WRONLY
					|O_TRUNC, 0644);
			dup2(tab_norme[0], STDOUT_FILENO);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		close(tab_norme[0]);
		exec_commands(env, tab, argv[tab_norme[2] + 2]);
	}
	dup2(pipefd[0], tab_norme[0]);
	close(pipefd[0]);
	close(pipefd[1]);
}
