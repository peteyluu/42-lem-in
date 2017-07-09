/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:35:10 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 13:35:24 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_node_vec(t_node_vec **nodes, int sz)
{
	if (!(*nodes = (t_node_vec*)malloc(sizeof(t_node_vec))))
		exit(-1);
	(*nodes)->log_len = 0;
	(*nodes)->alloc_len = sz;
	if (!((*nodes)->vec = (t_node**)malloc(sizeof(t_node*) * sz)))
		exit(-1);
}

void	pop_node_vec(t_node_vec **nodes, t_map **info)
{
	t_str_lst	*tmp;

	tmp = (*info)->path;
	while ((*info)->path)
	{
		add_node_vec(nodes, find_node(info, (*info)->path->s));
		(*info)->path = (*info)->path->next;
	}
	(*info)->path = tmp;
}

void	add_node_vec(t_node_vec **nodes, t_node *node)
{
	if ((*nodes)->log_len == (*nodes)->alloc_len)
		grow_node_vec(nodes);
	(*nodes)->vec[(*nodes)->log_len] = node;
	(*nodes)->log_len++;
}

void	grow_node_vec(t_node_vec **nodes)
{
	t_node_vec	*tmp;
	int		i;

	init_node_vec(&tmp, (*nodes)->alloc_len * 2);
	i = 0;
	while (i < (*nodes)->log_len)
	{
		tmp->vec[tmp->log_len] = (*nodes)->vec[i];
		tmp->log_len++;
		i++;
	}
	dispose_node_vec(nodes);
	*nodes = tmp;
}

void	dispose_node_vec(t_node_vec **nodes)
{
	free((*nodes)->vec);
	free(*nodes);
}
