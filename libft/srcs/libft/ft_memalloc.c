/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:21:29 by pluu              #+#    #+#             */
/*   Updated: 2017/05/09 18:47:58 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*new_mem;

	new_mem = NULL;
	new_mem = malloc(size);
	if (new_mem)
		ft_bzero(new_mem, size);
	return ((new_mem) ? new_mem : NULL);
}
