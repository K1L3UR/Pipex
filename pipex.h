/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <arnduran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:12:04 by arnduran          #+#    #+#             */
/*   Updated: 2023/02/23 19:27:55 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"

char	**extract_path(char **env);
char	*find_binaries(char **tab, char *bin_name);
void	print_tab(char **tab);
void	ft_freetab(char **tab);
//void    child_management(char **argv, int *tab_norme, char **env, char **tab);
int		child_management(char **argv, int *tab_norme, char **env, char **tab);
void	exec_commands(char **env, char **tab, char *argv);
int		ft_exit(char **tab);

#endif