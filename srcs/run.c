/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 13:39:31 by pluu              #+#    #+#             */
/*   Updated: 2017/07/09 13:49:06 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	str_lst_len(t_str_lst *path)
{
      int     len;

      len = 0;
      while (path)
      {
              len++;
              path = path->next;
      }
      return (len);
}

static void	init_run_vars(t_run *vars, t_map **info)
{
	int	len;

	len = str_lst_len((*info)->path);
	init_node_vec(&vars->nodes, len);
	pop_node_vec(&vars->nodes, info);
	vars->queue = NULL;
	vars->ant_num = 1;
	vars->len = len;
}

static void	handle_ant_move(t_run *vars)
{
	if (vars->nodes->vec[0]->ants && !vars->nodes->vec[1]->ants)
	{
		vars->nodes->vec[0]->ants--;
		vars->nodes->vec[1]->ants++;
		enqueue_pnode(&vars->queue, vars->ant_num, vars->nodes->vec[1]->data[0], 1);
		vars->ant_num++;
	}
}

static void	display(t_map **info, t_run *vars)
{
	while ((*info)->end->ants != (*info)->ants || vars->queue)
	{
		handle_ant_move(vars);
		vars->cnt = queue_len(vars->queue);
		while ((vars->cnt && (vars->curr = dequeue_pnode(&vars->queue))))
		{
			ft_printf("L%d-%s", vars->curr->ant_num, vars->curr->room);
			if (ft_strcmp(vars->curr->room, (*info)->end->data[0]))
			{
				vars->nodes->vec[vars->curr->idx]->ants--;
				vars->nodes->vec[vars->curr->idx + 1]->ants++;
				enqueue_pnode(&vars->queue, vars->curr->ant_num,
					vars->nodes->vec[vars->curr->idx + 1]->data[0], vars->curr->idx + 1);
			}
			free(vars->curr);
			if (--vars->cnt)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

void		run(t_map **info)
{
	t_run	vars;

	(*info)->start->ants = (*info)->ants;
	init_run_vars(&vars, info);
	if (vars.len > 2)
		display(info, &vars);
	else
	{
		while ((*info)->end->ants != (*info)->ants)
		{
			if (vars.nodes->vec[0]->ants)
			{
				vars.nodes->vec[0]->ants--;
				vars.nodes->vec[1]->ants++;
				ft_printf("L%d-%s", vars.ant_num, vars.nodes->vec[1]->data[0]);
				vars.ant_num++;
				if (vars.nodes->vec[0]->ants)
					ft_putchar(' ');
			}
		}
		ft_putchar('\n');
	}
	dispose_node_vec(&vars.nodes);
}
