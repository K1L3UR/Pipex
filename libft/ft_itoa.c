/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 22:32:36 by arnduran          #+#    #+#             */
/*   Updated: 2020/01/18 22:34:36 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_int(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*write_n(char *str, int n, size_t i)
{
	while (n > 9)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[i] = n + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	j;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648\0");
		return (str);
	}
	j = size_int(n);
	str = (char *)malloc(sizeof(char) * (j + 2));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str = write_n(str, n, j);
	str[j + 1] = '\0';
	return (str);
}
