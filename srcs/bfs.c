/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:54:22 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 13:56:15 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	prepend_str_lst(t_str_lst **path, char *s)
{
	t_str_lst	*tmp;

	if (!*path)
	{
		if (!(*path = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*path)->s = s;
		(*path)->next = NULL;
	}
	else
	{
		if (!(tmp = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		tmp->s = s;
		tmp->next = *path;
		*path = tmp;
	}
}

static void	add_path(t_map **info, t_hashentry *arr)
{
	t_str_lst	*path;
	unsigned long	key;

	path = NULL;
	key = hash((*info)->end->data[0]);
	if (!arr[key].key)
		return ;
	while (ft_strcmp(arr[key].key, (*info)->start->data[0]))
	{
		if (arr[key].key)
		{
			prepend_str_lst(&path, arr[key].key);
			key = hash(arr[key].val);
		}
	}
	prepend_str_lst(&path, arr[key].key);
	(*info)->path = path;
}

void	bfs(t_map **info)
{
	t_bfs	vars;

	init_hash(&vars.arr);
	insert_hash(&vars.arr, (*info)->start->data[0], "none");
	vars.queue = NULL;
	enqueue(&vars.queue, (*info)->start->data[0]);
	while ((vars.tmp = dequeue(&vars.queue)))
	{
		if (!ft_strcmp(vars.tmp, (*info)->end->data[0]))
			break ;
		vars.curr = find_node(info, vars.tmp);
		vars.tmp1 = vars.curr->links;
		while (vars.curr->links)
		{
			if (!is_in_hash(vars.arr, vars.curr->links->s))
			{
				insert_hash(&vars.arr, vars.curr->links->s, vars.curr->data[0]);
				enqueue(&vars.queue, vars.curr->links->s);
			}
			vars.curr->links = vars.curr->links->next;
		}
		vars.curr->links = vars.tmp1;
	}
	add_path(info, vars.arr);
	free(vars.arr);
}
