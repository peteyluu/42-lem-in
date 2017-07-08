/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:54:50 by pluu              #+#    #+#             */
/*   Updated: 2017/05/09 18:46:18 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (!alst)
		return ;
	if (!*alst)
		return ;
	if (!del)
		return ;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		tmp = (*alst)->next;
		free(*alst);
		*alst = tmp;
	}
	tmp = NULL;
}
