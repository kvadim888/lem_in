/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:33:10 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:23 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_error(int trigger, char const *msg)
{
	if (trigger)
	{
		ft_dprintf(2, "ERROR: %s\n", msg);
		exit(0);
	}
}

void	ft_warning(int trigger, char const *msg)
{
	if (trigger)
		ft_dprintf(2, "WARNING: %s\n", msg);
}
