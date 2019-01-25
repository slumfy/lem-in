/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pipe_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:49:37 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/16 14:59:28 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map	*map_create_elem(char **tab, int state)
{
	t_map	*new;

	if (!(new = (t_map*)ft_memalloc(sizeof(t_map))))
		exit(0);
	new->name = strdup(tab[0]);
	new->x = sizetoi(tab[1]);
	new->y = sizetoi(tab[2]);
	new->state = state;
	new->pipe = NULL;
	new->next = NULL;
	return (new);
}

void	map_pushback(t_map **begin_list, char **tab, int state)
{
	t_map	*tmp;

	if (*begin_list)
	{
		tmp = *begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = map_create_elem(tab, state);
	}
	else
		*begin_list = map_create_elem(tab, state);
}

t_pipe	*pipe_create_elem(char **tab)
{
	t_pipe	*new;

	if (!(new = (t_pipe*)ft_memalloc(sizeof(t_pipe))))
		exit(0);
	new->arg1 = strdup(tab[0]);
	new->arg2 = strdup(tab[1]);
	new->next = NULL;
	return (new);
}

void	pipe_pushback(t_pipe **begin_list, char **tab)
{
	t_pipe	*tmp;

	if (*begin_list)
	{
		tmp = *begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = pipe_create_elem(tab);
	}
	else
		*begin_list = pipe_create_elem(tab);
}
