/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:38:01 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:45:23 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	line_append(t_str_lst **lines, char *s)
{
	t_str_lst	*head;

	if (!*lines)
	{
		if (!(*lines = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*lines)->s = ft_strdup(s);
		(*lines)->next = NULL;
	}
	else
	{
		head = *lines;
		while ((*lines)->next)
			*lines = (*lines)->next;
		if (!((*lines)->next = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*lines)->next->s = ft_strdup(s);
		(*lines)->next->next = NULL;
		*lines = head;
	}
}

t_node	*find_node(t_map **info, char *name)
{
	t_node	*ret;
	t_node	*tmp;

	ret = NULL;
	if ((*info)->start && !ft_strcmp((*info)->start->data[0], name))
		return ((*info)->start);
	else if ((*info)->end && !ft_strcmp((*info)->end->data[0], name))
		return ((*info)->end);
	else
	{
		tmp = (*info)->rooms;
		while ((*info)->rooms)
		{
			if (!ft_strcmp((*info)->rooms->data[0], name))
			{
				ret = (*info)->rooms;
				break ;
			}
			(*info)->rooms = (*info)->rooms->next;
		}
		(*info)->rooms = tmp;
	}
	return (ret);
}

int	link_exist(t_node *node, char *s)
{
	t_str_lst	*tmp;

	tmp = node->links;
	while (node->links)
	{
		if (!ft_strcmp(node->links->s, s))
		{
			node->links = tmp;
			return (1);
		}
		node->links = node->links->next;
	}
	node->links = tmp;
	return (0);
}

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_link(char *s)
{
	t_is_room_link	vars;

	init_is_room_link(&vars);
	while (*s)
	{
		if (is_unicode(*s) && *s != '-')
			vars.data_flag = 1;
		else if (*s == '-')
		{
			if (vars.data_flag)
				vars.data++;
			vars.data_flag = 0;
			vars.delim++;
		}
		else
			return (0);
		s++;
	}
	if (vars.data_flag)
		vars.data++;
	return (vars.data == LINK_ROOM && vars.delim == LINK_HYPHEN ? 1 : 0);
}
