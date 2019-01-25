/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:03:58 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/24 17:01:04 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		read_stdin(t_data *data, int trig, char **line)
{
	if (!isant(line, data))
		return (-1);
	while (get_next_line(0, line) > 0)
	{
		if (!iscomment(*line))
		{
			if (trig == 0 && isroom(*line, data) == 1)
				ft_list_pushback(&data->raw_input, strdup(*line), 0);
			else if (isinst(*line) > 0)
				ft_list_pushback(&data->raw_input, strdup(*line), 0);
			else
				trig = 1;
			if (trig == 1 && ispipe(*line, data) == 1 && isstate(data) == 0)
				ft_list_pushback(&data->raw_input, strdup(*line), 0);
			else if (trig == 1)
				return (-1);
		}
		else if (iscomment(*line) && isstate(data) == 0)
			ft_list_pushback(&data->raw_input, strdup(*line), 0);
		else if (isstate(data) != 0)
			return (-1);
		ft_strdel(line);
	}
	return (1);
}

int		isant(char **str, t_data *data)
{
	if (get_next_line(0, str) > 0)
	{
		if (!ft_strisdigit(*str))
		{
			ft_strdel(str);
			return (0);
		}
		data->ant = sizetoi(*str);
		ft_list_pushback(&data->raw_input, strdup(*str), 0);
		ft_strdel(str);
		return (1);
	}
	return (0);
}

int		isroom(char *str, t_data *data)
{
	char	**tab;

	tab = ft_strsplit(str, 32);
	if (tab_len(tab) != 3 || tab[0][0] == 'L' || !ft_strisdigit(tab[1])
			|| !ft_strisdigit(tab[2]) || ft_strchr(str, '-'))
	{
		freetab(&tab);
		return (0);
	}
	if (isstate(data) != 0)
		map_pushback(&data->map, tab, isstate(data));
	else
		map_pushback(&data->map, tab, 0);
	freetab(&tab);
	return (1);
}

int		ispipe(char *str, t_data *data)
{
	char	**tab;

	tab = ft_strsplit(str, '-');
	if (tab_len(tab) != 2 || isminus(str) < 0
			|| ft_strequ(tab[0], tab[1]) == 1)
	{
		freetab(&tab);
		return (0);
	}
	pipe_pushback(&data->pipe, tab);
	freetab(&tab);
	return (1);
}
