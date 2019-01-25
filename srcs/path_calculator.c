/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_calculator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:11:19 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/25 11:28:28 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		dispatch_ant(t_data *data, size_t *n)
{
	size_t		i;
	int			test;
	long long	diff;

	i = 0;
	test = 0;
	diff = 0;
	while (data->path_tab[i] && (*n))
	{
		if (i > 0)
		{
			test = data->path_tab[i - 1]->ant;
			diff = data->path_tab[i]->size - data->path_tab[i - 1]->size + 1;
		}
		if (diff <= test)
		{
			data->path_tab[i]->ant += 1;
			(*n)--;
		}
		else
			break ;
		i++;
	}
	return (0);
}

void	pathfinder(t_data *data)
{
	size_t	nant;

	nant = data->ant;
	while (nant)
		dispatch_ant(data, &nant);
}
