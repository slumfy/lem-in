/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:35:33 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/24 16:49:21 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_overlap_path(t_data *data)
{
	int		i;
	int		j;
	t_path	**tmp;
	t_path	**tmp2;

	i = 0;
	tmp = data->path_tab;
	while (tmp[i])
	{
		j = i + 1;
		tmp2 = data->path_tab;
		while (tmp2[j])
		{
			if (path_verif(data, i, j))
			{
				delete_path(data, j);
				return (check_overlap_path(data));
			}
			j++;
		}
		i++;
	}
}

void	merge_ifeq_path(t_data *data, int n)
{
	t_path	*tmp;
	t_path	*tmp2;
	int		i;

	i = -1;
	while (++i < n)
	{
		tmp = data->path_tab[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			while (tmp2)
			{
				if (tmp2->room == tmp->room
						&& tmp->room->state == tmp2->room->state
						&& tmp->room->state == 0)
				{
					tmp->next = tmp2->next;
					data->path_tab[i]->size = path_len(&data->path_tab[i]);
				}
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	}
}

void	delete_path(t_data *data, int index)
{
	t_path	**tab;
	int		n;
	int		j;
	int		i;

	j = 0;
	i = 0;
	n = tab_struc_len(data->path_tab);
	if (!(tab = (t_path **)ft_memalloc(sizeof(t_path *) * (n))))
		exit(0);
	while (j < n)
	{
		if (j != index)
		{
			tab[i] = data->path_tab[j];
			i++;
		}
		j++;
	}
	free(data->path_tab);
	data->path_tab = tab;
}

int		check_ifpath(t_data *data)
{
	t_path	*tmp;
	int		end;
	int		start;

	start = 0;
	end = 0;
	tmp = data->global_path;
	while (tmp)
	{
		if (tmp->room->state == 1)
			start++;
		else if (tmp->room->state == 2)
			end++;
		tmp = tmp->next;
	}
	if (start == 0 || end == 0)
		return (0);
	return (1);
}

int		path_verif(t_data *data, int n1, int n2)
{
	t_path	*tmp1;
	t_path	*tmp2;

	tmp1 = data->path_tab[n1];
	while (tmp1)
	{
		tmp2 = data->path_tab[n2];
		while (tmp2)
		{
			if (ft_strequ(tmp1->room->name, tmp2->room->name) == 1
					&& tmp1->room->state == 0 && tmp2->room->state == 0)
				return (n2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	return (0);
}
