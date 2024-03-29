/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 22:34:11 by arnduran          #+#    #+#             */
/*   Updated: 2020/01/18 22:34:54 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char const *set, char c)
{
	size_t	i;

	i = 0;
	if (!(set))
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*result;

	k = 0;
	i = 0;
	if (!(s1))
		return (NULL);
	j = ft_strlen(s1);
	while (isinset(set, s1[i]) && s1[i])
		i++;
	while (j - 1 >= i && isinset(set, s1[j - 1]))
		j--;
	result = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!result)
		return (NULL);
	while (s1[i] && i < j)
	{
		result[k] = s1[i];
		i++;
		k++;
	}
	result[k] = '\0';
	return (result);
}
