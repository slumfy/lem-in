/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:43:46 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/16 15:00:56 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isminus(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '-')
			k++;
		i++;
	}
	if (k > 1)
		return (-6);
	else if (k == 0)
		return (-7);
	else
		return (1);
}

int		doublepipe(char **tab, t_data *data)
{
	t_pipe	*tmp;

	tmp = data->pipe;
	while (tmp)
	{
		if (ft_strequ(tmp->arg1, tab[0]) == 1
				&& ft_strequ(tmp->arg2, tab[1]) == 1)
			return (-11);
		if (ft_strequ(tmp->arg2, tab[0]) == 1
				&& ft_strequ(tmp->arg1, tab[1]) == 1)
			return (-11);
		tmp = tmp->next;
	}
	return (1);
}

int		isstate(t_data *data)
{
	t_list	*tmp;

	tmp = data->raw_input;
	while (tmp->next)
		tmp = tmp->next;
	if (isinst(tmp->data) == 1)
	{
		if (ft_strequ(tmp->data, "##end") == 1)
			return (2);
		else
			return (1);
	}
	return (0);
}

int		isinst(char *str)
{
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (1);
	else if (str[0] == '#' && str[1] == '#')
		return (2);
	return (0);
}

int		iscomment(char *str)
{
	if (str[0] == '#' && str[1] != '#')
		return (1);
	return (0);
}
