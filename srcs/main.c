/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:30:31 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 14:45:58 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_map(t_map **info)
{
	if (!(*info = (t_map*)malloc(sizeof(t_map))))
		exit(-1);
	(*info)->lines = NULL;
	(*info)->ants = 0;
	(*info)->start = NULL;
	(*info)->end = NULL;
	(*info)->rooms = NULL;
	(*info)->path = NULL;
}

static void	line_print(t_str_lst *lines)
{
	while (lines)
	{
		ft_putendl(lines->s);
		lines = lines->next;
	}
}

static void	path_print_lst(t_str_lst *path)
{
	while (path)
	{
		ft_putstr(path->s);
		path = path->next;
		if (path)
			ft_putstr(" -> ");
	}
	ft_putchar('\n');
}

int		main(void)
{
	t_map	*info;

	init_map(&info);
	if (!parser(&info))
		ft_putendl_fd("Error", 2);
	else
	{
		line_print(info->lines);
		path_print_lst(info->path);
		run(&info);
	}
	dispose_map(&info);
	return (0);
}
