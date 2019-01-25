/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_struc_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:09:26 by rvalenti          #+#    #+#             */
/*   Updated: 2019/01/20 06:13:25 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	tab_struc_len(t_path **path_tab)
{
	size_t	count;

	count = 0;
	while (path_tab[count])
		count++;
	return (count);
}
