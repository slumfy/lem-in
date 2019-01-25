/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:44:01 by rvalenti          #+#    #+#             */
/*   Updated: 2019/01/24 14:25:27 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ant_move(t_path *path, t_path *prev, t_data *data, int n)
{
	if (path->next && path->room->state != 1 && path->room->nbant == 1
			&& (path->next->room->nbant == 0 || path->next->room->state == 2))
	{
		path->next->room->nameant = path->room->nameant;
		path->room->nameant = 0;
		path->next->room->nbant++;
		path->room->nbant--;
		print_ant(path);
		if (prev->room->nbant && prev->room->state != 1)
			return (ant_move(data->path_tab[n], data->path_tab[n], data, n));
	}
	else if (path->next)
		return (ant_move(path->next, path, data, n));
	return (0);
}

int		ant_push(t_path *path, t_path *prev, t_data *data, int n)
{
	if (path->room->state == 1 && path->room->nbant
			&& (path->next->room->nbant == 0 || path->next->room->state == 2))
	{
		path->room->nbant--;
		path->room->nameant = data->ant - path->room->nbant;
		path->next->room->nameant = path->room->nameant;
		path->next->room->nbant++;
		print_ant(path);
	}
	else if (path->next && path->room->state != 1 && path->room->nbant == 1
			&& (path->next->room->nbant == 0 || path->next->room->state == 2))
	{
		path->next->room->nameant = path->room->nameant;
		path->room->nameant = 0;
		path->next->room->nbant++;
		path->room->nbant--;
		print_ant(path);
		if (prev->room->nbant)
			return (ant_push(data->path_tab[n], data->path_tab[n], data, n));
	}
	else if (path->next)
		return (ant_push(path->next, path, data, n));
	return (0);
}

void	print_ant(t_path *path)
{
	write(1, "L", 1);
	ft_putnbr(path->next->room->nameant);
	write(1, "-", 1);
	ft_putstr(path->next->room->name);
	write(1, " ", 1);
}

int		check_ant(t_data *data, int n)
{
	int		j;
	t_path	*tmp;

	j = 0;
	while (j < n)
	{
		tmp = data->path_tab[j];
		while (tmp)
		{
			if (tmp->room->nbant != 0 && tmp->room->state != 2)
				return (0);
			tmp = tmp->next;
		}
		j++;
	}
	return (1);
}

int		ant_path(t_data *data)
{
	size_t	i;
	size_t	n;
	size_t	count;

	count = tab_struc_len(data->path_tab);
	n = pipesize(data->start->pipe);
	if (n > count)
		n = count;
	while (!check_ant(data, n))
	{
		i = 0;
		while (i < n)
		{
			if (data->path_tab[i]->ant == 0)
				ant_move(data->path_tab[i], data->path_tab[i], data, i);
			else
			{
				ant_push(data->path_tab[i], data->path_tab[i], data, i);
				data->path_tab[i]->ant--;
			}
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
