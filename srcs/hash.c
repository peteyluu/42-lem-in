/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:57:37 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 13:58:06 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_in_hash(t_hashentry *arr, char *s)
{
	unsigned long	key;

	key = hash(s);
	if (arr[key].key && !ft_strcmp(arr[key].key, s))
		return (1);
	return (0);
}

void		init_hash(t_hashentry **arr)
{
	if (!(*arr = (t_hashentry*)malloc(sizeof(t_hashentry) * INT_MAX)))
		exit(-1);
}

void		insert_hash(t_hashentry **arr, char *s, char *val)
{
	unsigned long	key;

	key = hash(s);
	(*arr)[key].key = s;
	(*arr)[key].val = val;
}

unsigned long	hash(char *s)
{
	unsigned long	hash;
	int		c;

	hash = 5381;
	while ((c = *s++))
		hash = ((hash << 5) + hash) + c;
	return (hash % INT_MAX);
}

