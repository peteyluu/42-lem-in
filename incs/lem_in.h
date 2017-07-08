/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:36:43 by pluu              #+#    #+#             */
/*   Updated: 2017/07/08 16:33:33 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <limits.h>
# define ROOM_ATTR 3
# define ROOM_DELIM 2
# define LINK_ROOM 2
# define LINK_HYPHEN 1

enum
{
	def,
	ant,
	room,
	roomlink,
	start,
	end,
	comment
};

typedef struct			s_printnode
{
	int			ant_num;
	char			*room;
	int			idx;
	struct s_printnode	*next;
}				t_printnode;

typedef struct			s_hashentry
{
	char			*key;
	char			*val;
}				t_hashentry;

typedef struct			s_str_lst
{
	char			*s;
	struct s_str_lst	*next;
}				t_str_lst;

typedef struct			s_node
{
	int			ants;
	int			type;
	char			**data;
	t_str_lst		*links;
	struct s_node		*next;
}				t_node;

typedef struct			s_map
{
	t_str_lst		*lines;
	int			ants;
	t_node			*start;
	t_node			*end;
	t_node			*rooms;
	t_str_lst		*path;
}				t_map;

typedef struct			s_is_room_link
{
	int			data_flag;
	int			data;
	int			delim;
}				t_is_room_link;

typedef struct			s_node_vec
{
	t_node			**vec;
	int			log_len;
	int			alloc_len;
}				t_node_vec;

typedef struct			s_bfs
{
	t_hashentry		*arr;
	t_str_lst		*queue;
	t_str_lst		*tmp1;
	char			*tmp;
	t_node			*curr;
}				t_bfs;

typedef struct			s_run
{
	t_node_vec		*nodes;
	t_printnode		*queue;
	t_printnode		*curr;
	int			cnt;
	int			ant_num;
	int			len;
}				t_run;

/* printing */
void				enqueue_pnode(t_printnode **queue, int ant_num, char *room, int idx);
t_printnode			*dequeue_pnode(t_printnode **queue);
int				len_pnode(t_printnode *queue);

/* hash */
unsigned long			hash(char *s);
void				init_hash(t_hashentry **arr);
void				insert_hash(t_hashentry **arr, char *s, char *val);
int				is_in_hash(t_hashentry *arr, char *s);
void				add_path(t_map **info, t_hashentry *arr);
/* bfs */
void				bfs(t_map **info);
void				prepend_str_lst(t_str_lst **path, char *s);
/* queue funcs */
void				enqueue(t_str_lst **queue, char *s);
char				*dequeue(t_str_lst **queue);

void				run(t_map **info);
void				init_run_vars(t_run *vars, t_map **info);
void				display(t_map **info, t_run *vars);
void				handle_ant_move(t_run *vars);
void				init_node_vec(t_node_vec **nodes, int sz);
void				pop_node_vec(t_node_vec **nodes, t_map **info);
void				add_node_vec(t_node_vec **nodes, t_node *node);
void				grow_node_vec(t_node_vec **nodes);
void				dispose_node_vec(t_node_vec **nodes);
int				str_lst_len(t_str_lst *path);
void				init_map(t_map **info);
void				dispose_map(t_map **info);
void				dispose_nodes(t_node *nodes);
void				dispose_str_lst(t_str_lst *lines);
void				dispose_str_lst1(t_str_lst *path);
void				dispose_twodarr(char **arr);
void				line_print(t_str_lst *lines);
void				path_print_lst(t_str_lst *path);
int				parser(t_map **info);
int				is_map(t_map **info);
int				is_path(t_map **info);
void				line_append(t_str_lst **lines, char *s);
int				parse_line(char *s);
int				pop_attrs(t_map **info, int *type, char *s);
int				ft_isnumber(char *s);
int				is_room(char *s);
int				is_link(char *s);
void				init_is_room_link(t_is_room_link *vars);
int				is_unicode(int c);
int				is_room_dup(t_map *info, char *s);
void				room_append(t_node **room, char *s, int type);
int				link_append(t_map **info, char *origin, char *dest);
int				link_append_rooms(t_map **info, char *origin, char *dest);
int				link_append_hlpr(t_str_lst **links, char *dest);
void				link_new_append(t_str_lst **links, char *dest, int is_append);
int				link_add(t_map **info, char *s);
int				link_exist(t_node *node, char *s);
t_node				*find_node(t_map **info, char *name);

#endif
