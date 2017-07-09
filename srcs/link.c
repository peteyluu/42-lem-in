/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:14:44 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:43:18 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	link_new_append(t_str_lst **links, char *dest, int is_append)
{
	if (!is_append)
	{
		if (!(*links = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*links)->s = ft_strdup(dest);
		(*links)->next = NULL;
	}
	else
	{
		if (!((*links)->next = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*links)->next->s = ft_strdup(dest);
		(*links)->next->next = NULL;
	}
}

static int	link_append_hlpr(t_str_lst **links, char *dest)
{
	t_str_lst	*tmp;
	t_str_lst	*prev;

	if (!*links)
		link_new_append(links, dest, 0);
	else
	{
		tmp = *links;
		while (*links)
		{
			if (!ft_strcmp((*links)->s, dest))
			{
				*links = tmp;
				return (0);
			}
			prev = *links;
			*links = (*links)->next;
		}
		*links = prev;
		link_new_append(links, dest, 1);
		*links = tmp;
	}
	return (1);
}

static int	link_append_rooms(t_map **info, char *origin, char *dest)
{
	t_node	*tmp;

	tmp = (*info)->rooms;
	while ((*info)->rooms)
	{
		if (!ft_strcmp((*info)->rooms->data[0], origin))
		{
			if (!link_append_hlpr(&(*info)->rooms->links, dest))
			{
				(*info)->rooms = tmp;
				return (0);
			}
			else
				break ;
		}
		(*info)->rooms = (*info)->rooms->next;
	}
	(*info)->rooms = tmp;
	return (1);
}

static int	link_append(t_map **info, char *origin, char *dest)
{
	if ((*info)->start && !ft_strcmp((*info)->start->data[0], origin))
	{
		if (!link_append_hlpr(&(*info)->start->links, dest))
			return (0);
	}
	else if ((*info)->end && !ft_strcmp((*info)->end->data[0], origin))
	{
		if (!link_append_hlpr(&(*info)->end->links, dest))
			return (0);
	}
	else
	{
		if (!link_append_rooms(info, origin, dest))
			return (0);
	}
	return (1);
}

int		link_add(t_map **info, char *s)
{
	t_node	*origin;
	t_node	*dest;
	char	**data;

	data = ft_strsplit(s, '-');
	origin = find_node(info, data[0]);
	dest = find_node(info, data[1]);
	if (origin && dest && !link_exist(origin, data[1]) && !link_exist(dest, data[0]))
	{
		link_append(info, data[0], data[1]);
		link_append(info, data[1], data[0]);
	}
	dispose_twodarr(data);
	return (!origin || !dest ? 0 : 1);
}
