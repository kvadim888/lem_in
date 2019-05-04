/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:32:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_add(t_list *link)
{
	t_route		*route;

	route = link->content;
	route->vertex->status += (route->flow > 0) ? route->flow : 0;
}

static void	ft_letflow(t_list *lst)
{
	t_vertex	*vertex;

	vertex = lst->content;
	ft_lstiter(vertex->link, ft_add);
}

int			ft_simulate(t_graph *graph)
{
	t_list		*lst;

	ft_lstiter(graph->head, ft_letflow);
	lst = graph->head;
	while (lst)
	{
		if (lst->content != graph->end &&
			((t_vertex *) lst->content)->status > 1)
			return (0);
		lst = lst->next;
	}
	return (1);
}
