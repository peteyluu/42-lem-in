/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:51:38 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:59:04 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		enqueue(t_str_lst **queue, char *s)
{
	t_str_lst	*tmp;
	if (!*queue)
	{
		if (!(*queue = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*queue)->s = s;
		(*queue)->next = NULL;
	}
	else
	{
		tmp = *queue;
		while ((*queue)->next)
			*queue = (*queue)->next;
		if (!((*queue)->next = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*queue)->next->s = s;
		(*queue)->next->next = NULL;
		*queue = tmp;
	}
}

char		*dequeue(t_str_lst **queue)
{
	t_str_lst	*tmp;
	char		*ret;

	if (!*queue)
		return (NULL);
	tmp = *queue;
	*queue = (*queue)->next;
	ret = tmp->s;
	free(tmp);
	return (ret);	
}

int		queue_len(t_printnode *queue)
{
	int		ret;

	ret = 0;
	while (queue)
	{
		queue = queue->next;
		ret++;
	}
	return (ret);
}

void		enqueue_pnode(t_printnode **queue, int ant_num, char *room, int idx)
{
	t_printnode	*tmp;

	if (!*queue)
	{
		if (!(*queue = (t_printnode*)malloc(sizeof(t_printnode))))
			exit(-1);
		(*queue)->ant_num = ant_num;
		(*queue)->room = room;
		(*queue)->idx = idx;
		(*queue)->next = NULL;
	}
	else
	{
		tmp = *queue;
		while ((*queue)->next)
			*queue = (*queue)->next;
		if (!((*queue)->next = (t_printnode*)malloc(sizeof(t_printnode))))
			exit(-1);
		(*queue)->next->ant_num = ant_num;
		(*queue)->next->room = room;
		(*queue)->next->idx = idx;
		(*queue)->next->next = NULL;
		*queue = tmp;
	}
}

t_printnode	*dequeue_pnode(t_printnode **queue)
{
	t_printnode	*tmp;

	if (!*queue)
		return (NULL);
	tmp = *queue;
	*queue = (*queue)->next;
	tmp->next = NULL;
	return (tmp);
}
