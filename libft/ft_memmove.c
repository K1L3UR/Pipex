/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnduran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 22:33:01 by arnduran          #+#    #+#             */
/*   Updated: 2020/01/18 22:34:40 by arnduran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (s2 < s1)
		while (i < len)
		{
			s1[len - i - 1] = s2[len - i - 1];
			i++;
		}
	else
		while (len > 0)
		{
			*(s1++) = *(s2++);
			len--;
		}
	return (dst);
}
