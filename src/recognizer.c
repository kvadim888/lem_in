/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:33:10 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:23 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	ft_islabel(char *str)
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

int	ft_iscomment(char const *str)
{
	return (str && (*str == '#'));
}

int	ft_islink(char *str)
{
	return ((*str != '#') && !ft_strchr(str, ' ') && ft_strchr(str, '-'));
}

int	ft_isnumber(char *num)
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
