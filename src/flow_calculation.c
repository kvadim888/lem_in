/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:32:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Edmonds-Karp algorithm realisation (finding maximum flow of ants per step)
*/

static int	ft_vertexcmp(void const *route, void const *vertex)
{
	return (((t_route const *)route)->vertex == vertex);
}

void		ft_addflow(t_list *link)
{
	t_vertex	*curr_vertex;
	t_vertex	*next_vertex;
	t_list		*curr_link;
	t_list		*next_link;

	if (link->next)
	{
		curr_vertex = (t_vertex *)(link->content);
		next_vertex = (t_vertex *)(link->next->content);
		curr_link = ft_lstfind(curr_vertex->link, next_vertex, ft_vertexcmp);
		next_link = ft_lstfind(next_vertex->link, curr_vertex, ft_vertexcmp);
		((t_route *)curr_link->content)->flow += 1;
		((t_route *)next_link->content)->flow -= 1;
	}
}
