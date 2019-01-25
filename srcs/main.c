/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:14:08 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/25 11:28:34 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_data	*data;
	char	*line;

	line = NULL;
	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		return (0);
	read_stdin(data, 0, &line);
	ft_strdel(&line);
	if (!isvalid_room(data))
		error(-1);
	isvalid_map(data);
	link_pipe(data);
	set_dimension(data->start, data->start, 0);
	explore(data->start, data, NULL);
	pathlist_totab(data, -1, npath(data), data->global_path);
	merge_ifeq_path(data, tab_struc_len(data->path_tab));
	sort_path_tab(data->path_tab, tab_struc_len(data->path_tab));
	check_overlap_path(data);
	ft_print_list(&data->raw_input);
	pathfinder(data);
	ant_path(data);
	free_struct(data);
	return (0);
}
