/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:53:46 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/25 10:50:57 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_weight(t_map *tmp)
{
	if (tmp->weight < tmp->connex)
		return (0);
	else
		return (1);
}

int		priority(t_map *tmp, t_map *prev)
{
	size_t	i;
	t_map	*min;
	int		j;

	i = 0;
	min = tmp->pipe[0];
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i]->weight > min->weight)
			min = tmp->pipe[i];
		i++;
	}
	i = 0;
	j = 0;
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i]->state == 2 && (j = i))
			return (j);
		i++;
	}
	j = give_priority(tmp, prev, min);
	return (j);
}

int		give_priority(t_map *tmp, t_map *prev, t_map *min)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i] != prev && check_weight(tmp->pipe[i]) == 0)
		{
			if (tmp->pipe[i]->weight == min->weight
					&& tmp->pipe[i]->n >= min->n && tmp->pipe[i]->connex != -1)
			{
				min = tmp->pipe[i];
				j = i;
			}
			else if (tmp->pipe[i]->weight <= min->weight
						&& tmp->pipe[i]->connex != -1)
			{
				min = tmp->pipe[i];
				j = i;
			}
		}
		i++;
	}
	return (j);
}

int		check_start(t_map *tmp)
{
	size_t	i;

	i = 0;
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i]->state == 2 && tmp->pipe[i]->weight > 0)
			return (1);
		i++;
	}
	i = 0;
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i]->connex >= 0
				&& tmp->pipe[i]->weight < tmp->pipe[i]->connex)
			return (0);
		i++;
	}
	return (1);
}

int		explore(t_map *tmp, t_data *data, t_map *prev)
{
	size_t	i;

	i = priority(tmp, prev);
	tmp->weight++;
	path_pushback(&data->global_path, tmp, 0);
	if (tmp->state == 1 && check_start(tmp) == 1)
		return (1);
	if (tmp->state == 2)
		return (explore(data->start, data, NULL));
	if (tmp->pipe[i] != prev && tmp->pipe[i]->connex != -1)
		return (explore(tmp->pipe[i], data, tmp));
	return (explore(data->start, data, NULL));
}
