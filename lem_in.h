/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:14:56 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/25 11:28:51 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include <string.h>
# include <stdlib.h>

typedef struct		s_map
{
	char			*name;
	size_t			x;
	size_t			y;
	long			n;
	int				state;
	long			weight;
	size_t			nbant;
	size_t			nameant;
	long			connex;
	struct s_map	**pipe;
	struct s_map	*next;
}					t_map;

typedef struct		s_pipe
{
	char			*arg1;
	char			*arg2;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_path
{
	t_map			*room;
	size_t			size;
	long			ant;
	struct s_path	*freenext;
	struct s_path	*next;
}					t_path;

typedef struct		s_data
{
	t_map			*map;
	t_map			*start;
	t_map			*m_end;
	t_pipe			*pipe;
	t_pipe			*p_end;
	t_path			*global_path;
	t_path			**path_tab;
	t_path			*pth_end;
	t_list			*raw_input;
	int				errcode;
	size_t			ant;
}					t_data;

/*
**	LIST FUNCTION (t_pipe, t_map)
*/
void				map_pushback(t_map **begin_list, char **tab, int state);
void				pipe_pushback(t_pipe **begin_list, char **tab);
void				path_pushback(t_path **begin, t_map *room, size_t size);
t_map				*map_create_elem(char **tab, int state);
t_path				*path_create_elem(t_map *room, size_t size);
t_pipe				*pipe_create_elem(char **tab);
size_t				path_len(t_path **begin_list);
/*
**	CHECKER	MAP
*/
int					isvalid_pipe(t_data *data);
int					isvalid_map(t_data *data);
int					isvalid_room(t_data *data);
int					count_state(t_data *data);
/*
**	CHECKER STDIN
*/
int					isant(char **str, t_data *data);
int					isroom(char *str, t_data *data);
int					ispipe(char *str, t_data *data);
int					isinst(char *str);
int					isminus(char *line);
int					iscomment(char *str);
int					isstate(t_data *data);
/*
**	CHECKER PATH
*/
int					check_ifpath(t_data *data);
void				check_ifend(t_map *tmp);
void				check_overlap_path(t_data *data);
void				merge_ifeq_path(t_data *data, int n);
void				delete_path(t_data *data, int index);
int					path_verif(t_data *data, int n1, int n2);
/*
**	EXPLORE
*/
int					check_weight(t_map *tmp);
int					check_weight(t_map *tmp);
int					explore(t_map *tmp, t_data *data, t_map *prev);
int					priority(t_map *tmp, t_map *prev);
int					give_priority(t_map *tmp, t_map *prev, t_map *min);
int					count_real_pipe(t_map *map, t_map *prev);
int					check_dead_end(t_map *map, t_map *prev);
void				pathlist_totab(t_data *data, size_t i,
					size_t len, t_path *tmp);
void				swap_totab(t_path **start, t_path **prev, t_path **tmp);
void				assign_path(t_path *s, t_path *t, t_path *p);
void				sort_path_tab(t_path **path_tab, size_t len);
void				count_connex(t_map *tmp, t_map *prev);
size_t				npath(t_data *data);
size_t				pipesize(t_map **pipe);
void				set_dimension(t_map *tmp, t_map *prev, size_t dim);
int					go_explore(t_map *tmp);
/*
** ANT MOVE
*/
int					ant_move(t_path *path, t_path *prev, t_data *data, int n);
int					ant_push(t_path *path, t_path *prev, t_data *data, int n);
int					check_ant(t_data *data, int n);
int					ant_path(t_data *data);
int					dispatch_ant(t_data *data, size_t *n);
void				print_ant(t_path *path);
void				pathfinder(t_data *data);
size_t				pathcalculator(t_data *data, size_t i);
/*
**	PARSER
*/
int					read_stdin(t_data *data, int trig, char **line);
void				link_pipe(t_data *data);
void				assign_pipe(t_map *map, t_data *data, size_t n);
t_map				*search_map_address(char *str, t_data *data);
/*
** TOOLS
*/
int					tab_len(char **str);
void				freetab(char ***tab);
void				free_map(t_data *data);
void				free_path(t_data *data);
void				free_pipe(t_data *data);
void				free_struct(t_data *data);
void				error(int n);
size_t				sizetoi(char *str);
size_t				pipe_nbr(t_map *map, t_pipe *pipe);
size_t				tab_struc_len(t_path **pipe);
#endif
