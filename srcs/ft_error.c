/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:52:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/25 11:03:19 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(int n)
{
	if (n == -1)
		ft_putendl_fd("Error (-1) : Bad room declaration.", 2);
	else if (n == -2)
		ft_putendl_fd("Error (-2) : Bad tunnel declaration.", 2);
	else if (n == -3)
		ft_putendl_fd("Error (-3) : No path between Start and End.", 2);
	exit(n);
}
