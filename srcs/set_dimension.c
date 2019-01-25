/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dimension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 09:53:14 by rvalenti          #+#    #+#             */
/*   Updated: 2019/01/24 10:18:08 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_dimension(t_map *tmp, t_map *prev, size_t dim)
{
	int	i;

	i = go_explore(prev);
	if (tmp->connex != -1)
		tmp->n = dim;
	else
		tmp->n = -2;
	if (i >= 0)
		set_dimension(prev->pipe[i], prev, dim);
	i = go_explore(tmp);
	if (i >= 0)
		set_dimension(tmp->pipe[i], tmp, dim + 1);
}

int		go_explore(t_map *tmp)
{
	size_t	i;

	i = 0;
	while (tmp->pipe[i])
	{
		if (tmp->pipe[i]->n == -1)
			return (i);
		i++;
	}
	return (-1);
}
