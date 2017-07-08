/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:04:18 by pluu              #+#    #+#             */
/*   Updated: 2017/05/09 18:48:09 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*s1;
	const char	*s2;
	size_t		cnt;

	if (n)
	{
		s1 = dst;
		s2 = src;
		cnt = 0;
		while (n--)
		{
			if ((*s1++ = *s2++) == c)
				return (dst + cnt + 1);
			cnt++;
		}
	}
	return (0);
}
