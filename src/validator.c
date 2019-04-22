/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:34:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/03 17:34:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_label(char *str)
{
	if (*str == '#')
	{
		if (ft_strequ(str, "##start"))
			return (1);
		if (ft_strequ(str, "##end"))
			return (2);
	}
	return (0);
}

int			ft_islink(char *str)
{
	return ((*str != '#') && !ft_strchr(str, ' ') && ft_strchr(str, '-'));
}

int 		ft_isnumber(char *num)
{
	while (ft_iswhspace(*num))
		num++;
	if (*num == '-')
		num++;
	while (ft_isdigit(*num))
		num++;
	while (ft_iswhspace(*num))
		num++;
	return (*num == '\0');
}

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
	ft_error((ft_strsplitlen(split) != 3), "split != 3");
	vertex->name = split[0];
	ft_error(!ft_isnumber(split[1]) || !ft_isnumber(split[2]),
			 "Invalid room coordinates");
	vertex->x = ft_atoi(split[1]);
	vertex->y = ft_atoi(split[2]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	ft_memdel((void **)&split);
}
