/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:30:31 by pluu              #+#    #+#             */
/*   Updated: 2017/07/08 16:31:54 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
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

void	run(t_map **info)
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

void	init_run_vars(t_run *vars, t_map **info)
{
	int	len;

	len = str_lst_len((*info)->path);
	init_node_vec(&vars->nodes, len);
	pop_node_vec(&vars->nodes, info);
	vars->queue = NULL;
	vars->ant_num = 1;
	vars->len = len;
}

void	display(t_map **info, t_run *vars)
{
	while ((*info)->end->ants != (*info)->ants || vars->queue)
	{
		handle_ant_move(vars);
		vars->cnt = len_pnode(vars->queue);
		while ((vars->cnt && (vars->curr = dequeue_pnode(&vars->queue))))
		{
			ft_printf("L%d-%s", vars->curr->ant_num, vars->curr->room);
			if (ft_strcmp(vars->curr->room, (*info)->end->data[0]))
			{
				vars->nodes->vec[vars->curr->idx]->ants--;
				vars->nodes->vec[vars->curr->idx + 1]->ants++;
				enqueue_pnode(&vars->queue, vars->curr->ant_num, vars->nodes->vec[vars->curr->idx + 1]->data[0], vars->curr->idx + 1);
			}
			free(vars->curr);
			if (--vars->cnt)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

void	handle_ant_move(t_run *vars)
{
	if (vars->nodes->vec[0]->ants && !vars->nodes->vec[1]->ants)
	{
		vars->nodes->vec[0]->ants--;
		vars->nodes->vec[1]->ants++;
		enqueue_pnode(&vars->queue, vars->ant_num, vars->nodes->vec[1]->data[0], 1);
		vars->ant_num++;
	}
}

int	len_pnode(t_printnode *queue)
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

void	enqueue_pnode(t_printnode **queue, int ant_num, char *room, int idx)
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

int   str_lst_len(t_str_lst *path)
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

void	init_map(t_map **info)
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

/* dispose string links lst */
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

/* dispose string path lst */
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

void	line_print(t_str_lst *lines)
{
	while (lines)
	{
		ft_putendl(lines->s);
		lines = lines->next;
	}
}

void	path_print_lst(t_str_lst *path)
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

int	parser(t_map **info)
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

int	is_map(t_map **info)
{
	if (!(*info)->ants)
		return (0);
	else if (!(*info)->start || !(*info)->end)
		return (0);
	else if (!is_path(info))
		return (0);
	return (1);
}

int	is_path(t_map **info)
{
	bfs(info);
	return ((*info)->path ? 1 : 0);
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

void	add_path(t_map **info, t_hashentry *arr)
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

void	prepend_str_lst(t_str_lst **path, char *s)
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

int	is_in_hash(t_hashentry *arr, char *s)
{
	unsigned long	key;

	key = hash(s);
	if (arr[key].key && !ft_strcmp(arr[key].key, s))
		return (1);
	return (0);
}

void	init_hash(t_hashentry **arr)
{
	if (!(*arr = (t_hashentry*)malloc(sizeof(t_hashentry) * INT_MAX)))
		exit(-1);
}

void	insert_hash(t_hashentry **arr, char *s, char *val)
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

void	enqueue(t_str_lst **queue, char *s)
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

char	*dequeue(t_str_lst **queue)
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

int	parse_line(char *s)
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

int	pop_attrs(t_map **info, int *type, char *s)
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

int	link_add(t_map **info, char *s)
{
	t_node	*origin;
	t_node	*dest;
	char	**data;

	data = ft_strsplit(s, '-');
	origin = find_node(info, data[0]);
	dest = find_node(info, data[1]);
	if (origin && dest && !link_exist(origin, data[1]) && !link_exist(dest, data[0]))
	{
		link_append(info, data[0], data[1]);
		link_append(info, data[1], data[0]);
	}
	dispose_twodarr(data);
	return (!origin || !dest ? 0 : 1);
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

int	link_append(t_map **info, char *origin, char *dest)
{
	if ((*info)->start && !ft_strcmp((*info)->start->data[0], origin))
	{
		if (!link_append_hlpr(&(*info)->start->links, dest))
			return (0);
	}
	else if ((*info)->end && !ft_strcmp((*info)->end->data[0], origin))
	{
		if (!link_append_hlpr(&(*info)->end->links, dest))
			return (0);
	}
	else
	{
		if (!link_append_rooms(info, origin, dest))
			return (0);
	}
	return (1);
}

int	link_append_rooms(t_map **info, char *origin, char *dest)
{
	t_node	*tmp;

	tmp = (*info)->rooms;
	while ((*info)->rooms)
	{
		if (!ft_strcmp((*info)->rooms->data[0], origin))
		{
			if (!link_append_hlpr(&(*info)->rooms->links, dest))
			{
				(*info)->rooms = tmp;
				return (0);
			}
			else
				break ;
		}
		(*info)->rooms = (*info)->rooms->next;
	}
	(*info)->rooms = tmp;
	return (1);
}

int	link_append_hlpr(t_str_lst **links, char *dest)
{
	t_str_lst	*tmp;
	t_str_lst	*prev;

	if (!*links)
		link_new_append(links, dest, 0);
	else
	{
		tmp = *links;
		while (*links)
		{
			if (!ft_strcmp((*links)->s, dest))
			{
				*links = tmp;
				return (0);
			}
			prev = *links;
			*links = (*links)->next;
		}
		*links = prev;
		link_new_append(links, dest, 1);
		*links = tmp;
	}
	return (1);
}

void	link_new_append(t_str_lst **links, char *dest, int is_append)
{
	if (!is_append)
	{
		if (!(*links = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*links)->s = ft_strdup(dest);
		(*links)->next = NULL;
	}
	else
	{
		if (!((*links)->next = (t_str_lst*)malloc(sizeof(t_str_lst))))
			exit(-1);
		(*links)->next->s = ft_strdup(dest);
		(*links)->next->next = NULL;
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

void	init_is_room_link(t_is_room_link *vars)
{
	vars->data_flag = 0;
	vars->data = 0;
	vars->delim = 0;
}

int	is_unicode(int c)
{
	return (c < (1 << 21) ? 1 : 0);
}
