/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <arnduran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:14:55 by arnduran          #+#    #+#             */
/*   Updated: 2023/02/23 01:52:20 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_commands(char **env, char **tab, char *argv)
{
	char	**avtab;
	char	*s;

	avtab = ft_split(argv, ' ');
	if (!(avtab))
		exit((perror("ft_split"), ft_freetab(tab), 0));
	s = find_binaries(tab, *avtab);
	if (!s)
		exit((ft_freetab(tab), ft_freetab(avtab), EXIT_FAILURE));
	execve(s, avtab, env);
	perror("execve");
	free(s);
	ft_freetab(tab);
	free(avtab);
	exit(EXIT_FAILURE);
}

//tab[0] = fd_in[0];
//tab[1] = nb_commands;
//tab[2] = i; (nombre d'occurence pour la boucle)
int	exec(char **argv, int argc, char **env, char **tab)
{
	int		i;
	int		tab_norme[3];

	tab_norme[1] = argc - 3;
	tab_norme[2] = -1;
	tab_norme[0] = dup(STDIN_FILENO);
	while (++tab_norme[2] < tab_norme[1])
		child_management(argv, tab_norme, env, tab);
	close(tab_norme[0]);
	i = -1;
	while (++i < tab_norme[1])
		wait(NULL);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	char	**tab;

	if (argc < 5)
		exit((ft_putstr_fd("Need 5 argv at least", 1), 0));
	tab = extract_path(env);
	if (!(tab))
		return (0);
	exec(argv, argc, env, tab);
	ft_freetab(tab);
	return (0);
}
