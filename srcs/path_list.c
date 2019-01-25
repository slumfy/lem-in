/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:45:30 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/24 16:44:02 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*path_create_elem(t_map *room, size_t size)
{
	t_path	*new;

	if (!(new = (t_path*)ft_memalloc(sizeof(t_path))))
		exit(0);
	new->room = room;
	new->size = size;
	new->next = NULL;
	new->freenext = NULL;
	return (new);
}

void	path_pushback(t_path **begin, t_map *room, size_t size)
{
	t_path	*tmp;

	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path_create_elem(room, size);
		tmp->freenext = tmp->next;
	}
	else
		*begin = path_create_elem(room, size);
}

size_t	path_len(t_path **begin_list)
{
	t_path	*tmp;
	size_t	i;

	i = 0;
	tmp = *begin_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

size_t	npath(t_data *data)
{
	size_t	i;
	t_path	*tmp;

	tmp = data->global_path;
	i = 0;
	while (tmp)
	{
		if (tmp->room->state == 2)
			i++;
		tmp = tmp->next;
	}
	return (i + 1);
}
