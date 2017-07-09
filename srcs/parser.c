/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:03:09 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:06:08 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	parse_line(char *s)
{
	if (ft_isnumber(s))
		return (ant);
	else if (is_room(s))
		return (room);
	else if (is_link(s))
		return (roomlink);
	else if (!ft_strcmp("##start", s))
		return (start);
	else if (!ft_strcmp("##end", s))
		return (end);
	else if (s[0] == '#')
		return (comment);
	return (0);
}

static int	pop_attrs(t_map **info, int *type, char *s)
{
	if (type[0] == ant)
	{
		if ((*info)->ants)
			return (0);
		(*info)->ants = ft_atoi(s);
	}
	else if (type[0] == start || type[0] == end)
	{
		if ((type[0] == start && ((*info)->start || is_room_dup(*info, s))) ||
			(type[0] == end && ((*info)->end || is_room_dup(*info, s))))
			return (0);
		if (type[0] == start)
			room_append(&(*info)->start, s, type[0]);
		else
			room_append(&(*info)->end, s, type[0]);

	}
	else if (type[0] == room)
	{
		if (is_room_dup(*info, s))
			return (0);
		room_append(&(*info)->rooms, s, type[0]);
	}
	else if (type[0] == roomlink)
		return (!link_add(info, s) ? 0 : 1);
	return (1);
}

static int	is_path(t_map **info)
{
	bfs(info);
	return ((*info)->path ? 1 : 0);
}

static int	is_map(t_map **info)
{
	if (!(*info)->ants)
		return (0);
	else if (!(*info)->start || !(*info)->end)
		return (0);
	else if (!is_path(info))
		return (0);
	return (1);
}

int		parser(t_map **info)
{
	char	*s;
	int	type[2];
	int	tmp;

	while (get_next_line(0, &s))
	{
		type[0] = parse_line(s);
		if (type[0] == start || type[0] == end)
		{
			line_append(&(*info)->lines, s);
			free(s);
			get_next_line(0, &s);
			type[1] = parse_line(s);
		}
		line_append(&(*info)->lines, s);
		tmp = pop_attrs(info, type, s);
		free(s);
		if (!tmp || !type[0] || ((type[0] == start || type[0] == end) && type[1] != room))
			return (0);
		type[1] = none;
	}
	return (is_map(info));
}
