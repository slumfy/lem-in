/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 07:48:15 by rvalenti          #+#    #+#             */
/*   Updated: 2019/01/25 11:06:03 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	link_pipe(t_data *data)
{
	t_map	*tmp;
	size_t	n;

	tmp = data->map;
	while (tmp)
	{
		n = pipe_nbr(tmp, data->pipe);
		if (n)
		{
			if (!(tmp->pipe = (t_map **)ft_memalloc(sizeof(t_map *) * (n + 1))))
				return ;
			assign_pipe(tmp, data, n);
		}
		tmp->n = -1;
		tmp = tmp->next;
	}
	if (!isvalid_pipe(data))
		error(-1);
	count_connex(data->map, NULL);
	check_ifend(data->map);
}

void	assign_pipe(t_map *map, t_data *data, size_t n)
{
	t_map	**tmp;
	t_pipe	*tmpipe;
	size_t	i;

	i = 0;
	tmp = map->pipe;
	tmpipe = data->pipe;
	while (i <= n && tmpipe)
	{
		if (ft_strequ(map->name, tmpipe->arg1))
		{
			tmp[i] = search_map_address(tmpipe->arg2, data);
			i++;
		}
		if (ft_strequ(map->name, tmpipe->arg2))
		{
			tmp[i] = search_map_address(tmpipe->arg1, data);
			i++;
		}
		tmpipe = tmpipe->next;
	}
}

t_map	*search_map_address(char *str, t_data *data)
{
	t_map *tmp;

	tmp = data->map;
	while (tmp)
	{
		if (ft_strequ(tmp->name, str))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	pipe_nbr(t_map *map, t_pipe *pipe)
{
	t_pipe	*tmp;
	size_t	n;

	tmp = pipe;
	n = 0;
	while (pipe)
	{
		if (ft_strequ(map->name, pipe->arg1))
			n++;
		if (ft_strequ(map->name, pipe->arg2))
			n++;
		pipe = pipe->next;
	}
	return (n);
}
