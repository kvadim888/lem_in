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

int		ft_label(char *str)
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

int		ft_islink(char *str)
{
	return ((*str != '#') && !ft_strchr(str, ' ') && ft_strchr(str, '-'));
}

int 	ft_isnumber(char *num)
{
	char *start;

	start = num;
	while (ft_iswhspace(*num))
		num++;
	if (*num == '-')
		num++;
	while (ft_isdigit(*num))
		num++;
	if (ft_iswhspace(*num) || *num == '\0')
		return ((int)(num - start));
	else
		return (0);
}

int		ft_readvertex(char *str, t_vertex *vertex)
{
	int		i;
	int		len;

	vertex->status = 0;
	vertex->root = NULL;
	vertex->link = NULL;
	i = 0;
	while (ft_isprint(str[i]) && !ft_iswhspace(str[i]) && (str[i] != '-'))
		i++;
	if (!ft_iswhspace(str[i]))
		return (0);
	vertex->name = ft_strsub(str, 0, (size_t)i);
	str += i;
	if ((len = ft_isnumber(str)) > 0)
		vertex->x = ft_atoi(str);
	else
		return (0);
	str += len;
	if ((len = ft_isnumber(str)) > 0)
		vertex->y = ft_atoi(str);
	else
		return (0);
	str += len;
	while (ft_iswhspace(*str))
		str++;
	vertex->root = NULL;
	vertex->link = NULL;
	vertex->status = NULL;
	return (*str == '\0');
}

