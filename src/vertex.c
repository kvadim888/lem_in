/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:34:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/03 17:34:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_space(char *c)
{
	if (ft_iswhspace(*c))
		*c =  ' ';
}

void		ft_readvertex(char *str, t_vertex *vertex)
{
	char 	**split;

	ft_striter(str, ft_space);
	split = ft_strsplit(str, ' ');
	ft_error((ft_strsplitlen(split) != 3)
			|| !ft_isnumber(split[1]) || !ft_isnumber(split[2]), ERR_FROOM);
	vertex->name = split[0];
	vertex->x = ft_atoi(split[1]);
	vertex->y = ft_atoi(split[2]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_memdel((void **)&split);
}
