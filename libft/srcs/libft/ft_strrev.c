/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:19:26 by pluu              #+#    #+#             */
/*   Updated: 2017/05/09 18:56:01 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*start;
	char	*end;
	char	tmp;

	if (!s)
		return (NULL);
	start = s;
	end = s + (ft_strlen(s) - 1);
	while (end > start)
	{
		if (*start == '-')
		{
			start++;
			continue ;
		}
		tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
	return (s);
}
