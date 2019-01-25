/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_totab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:42:35 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/24 16:43:53 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	swap_totab(t_path **start, t_path **prev, t_path **tmp)
{
	*prev = *tmp;
	*tmp = (*tmp)->next;
	*start = *tmp;
	(*prev)->next = NULL;
}

void	pathlist_totab(t_data *data, size_t i, size_t len, t_path *tmp)
{
	size_t	j;
	t_path	*start;
	t_path	*prev;

	start = NULL;
	if (!(data->path_tab = (t_path **)ft_memalloc(sizeof(t_path*) * len)))
		exit(0);
	while (++i < len)
	{
		j = 0;
		while (tmp)
		{
			if (tmp->room->state == 1 && (start = tmp))
				j = 0;
			if (tmp->room->state == 2 && (data->path_tab[i] = start))
			{
				start->size = j;
				swap_totab(&start, &prev, &tmp);
				break ;
			}
			else
				tmp = tmp->next;
			j++;
		}
	}
}
