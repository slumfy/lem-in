/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_connex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:37:31 by rvalenti          #+#    #+#             */
/*   Updated: 2019/01/25 11:05:40 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	count_connex(t_map *tmp, t_map *prev)
{
	size_t	i;

	i = 0;
	while (tmp->pipe[i] && (tmp->connex == 0 || tmp->connex == -2))
	{
		if (tmp->pipe[i]->connex == 0 && tmp->pipe[i] != prev)
		{
			tmp->connex = -2;
			count_connex(tmp->pipe[i], tmp);
		}
		i++;
	}
	if (check_dead_end(tmp, prev) && tmp->state == 0)
		tmp->connex = -1;
	else if (tmp->state != 0)
		tmp->connex = pipesize(tmp->pipe);
	else
		tmp->connex = count_real_pipe(tmp, prev);
}

void	check_ifend(t_map *tmp)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (tmp)
	{
		if (tmp->state == 1)
			start++;
		else if (tmp->state == 2)
		{
			if (tmp->connex <= 0)
				error(-3);
			end++;
		}
		tmp = tmp->next;
	}
	if (!start || !end)
		error(-3);
}

int		count_real_pipe(t_map *map, t_map *prev)
{
	t_map	**tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = map->pipe;
	while (tmp[i])
	{
		if ((tmp[i]->connex > 0 || tmp[i]->connex == -2) && tmp[i] != prev)
			j++;
		i++;
	}
	return (j);
}

int		check_dead_end(t_map *map, t_map *prev)
{
	t_map	**tmp;
	size_t	i;

	i = 0;
	tmp = map->pipe;
	while (tmp[i])
	{
		if ((tmp[i]->connex > 0 || tmp[i]->connex == -2) && tmp[i] != prev)
			return (0);
		i++;
	}
	return (1);
}
