/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:30:13 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 13:31:34 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dispose_map(t_map **info)
{
	dispose_str_lst((*info)->lines);
	dispose_nodes((*info)->start);
	dispose_nodes((*info)->end);
	dispose_nodes((*info)->rooms);
	dispose_str_lst1((*info)->path);
	free(*info);
}

void	dispose_nodes(t_node *nodes)
{
	t_node	*tmp;

	while (nodes)
	{
		dispose_twodarr(nodes->data);
		dispose_str_lst(nodes->links);
		tmp = nodes;
		nodes = nodes->next;
		free(tmp);
	}
}

void	dispose_str_lst(t_str_lst *lines)
{
	t_str_lst	*tmp;

	while (lines)
	{
		if (lines->s)
			free(lines->s);
		tmp = lines;
		lines = lines->next;
		free(tmp);
	}
}

void	dispose_str_lst1(t_str_lst *path)
{
	t_str_lst	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

void	dispose_twodarr(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		free(data[i++]);
	free(data);
}
