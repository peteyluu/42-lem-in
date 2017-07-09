/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:11:17 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:44:52 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_is_room_link(t_is_room_link *vars)
{
	vars->data_flag = 0;
	vars->data = 0;
	vars->delim = 0;
}

void	room_append(t_node **room, char *s, int type)
{
	t_node	*tmp;

	if (!*room)
	{
		if (!(*room = (t_node*)malloc(sizeof(t_node))))
			exit(-1);
		(*room)->ants = 0;
		(*room)->type = type;
		(*room)->data = ft_strsplit(s, ' ');
		(*room)->links = NULL;
		(*room)->next = NULL;
	}
	else
	{
		tmp = *room;
		while ((*room)->next)
			*room = (*room)->next;
		if (!((*room)->next = (t_node*)malloc(sizeof(t_node))))
			exit(-1);
		(*room)->next->ants = 0;
		(*room)->next->type = type;
		(*room)->next->data = ft_strsplit(s, ' ');
		(*room)->next->links = NULL;
		(*room)->next->next = NULL;
		*room = tmp;
	}
}

int	is_room_dup(t_map *info, char *s)
{
	t_node	*tmp;
	char	**data;
	int	ret;

	ret = 0;
	data = ft_strsplit(s, ' ');
	if ((info->start && !ft_strcmp(info->start->data[0], data[0])) ||
		(info->end && !ft_strcmp(info->end->data[0], data[0])))
		ret = 1;
	if (info->rooms)
	{
		tmp = info->rooms;
		while (info->rooms)
		{
			if (!ft_strcmp(info->rooms->data[0], data[0]))
			{
				ret = 1;
				break ;
			}
			info->rooms = info->rooms->next;
		}
		info->rooms = tmp;
	}
	dispose_twodarr(data);
	return (ret);
}

int	is_room(char *s)
{
	t_is_room_link	vars;

	if (*s == 'L')
		return (0);
	init_is_room_link(&vars);
	while (*s)
	{
		if (!vars.delim && is_unicode(*s) && *s != ' ' && *s != '-')
			vars.data_flag = 1;
		else if (vars.delim >= 1 && (ft_isdigit(*s) || (*s == '-' && !vars.data_flag)))
			vars.data_flag = 1;
		else if (*s == ' ')
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
	return (vars.data == ROOM_ATTR && vars.delim == ROOM_DELIM ? 1 : 0);
}

int	is_unicode(int c)
{
	return (c < (1 << 21) ? 1 : 0);
}
