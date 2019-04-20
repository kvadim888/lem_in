/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:55:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 17:55:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_namecmp(void const *content1, void const *content2)
{
	t_vertex const	*vertex1;
	char const		*name;

	vertex1 = content1;
	name = content2;
	return (ft_strequ(vertex1->name, name));
}

int			ft_linkvertex(t_graph *graph, char *name1, char *name2)
{
	t_list	*v1;
	t_list	*v2;

	v1 = ft_lstfind(graph->head, name1, ft_namecmp);
	ft_error((v1 == NULL), ERR_UNKNOWN);
	v2 = ft_lstfind(graph->head, name2, ft_namecmp);
	ft_error((v2 == NULL), ERR_UNKNOWN);
	return (ft_newlink(v1->content, v2->content) &&
			ft_newlink(v2->content, v1->content));
}

static int	ft_routecmp(void const *content1, void const *content2)
{
	t_route const	*r1;
	t_route const	*r2;

	r1 = content1;
	r2 = content2;
	return (ft_strequ(r1->vertex->name, r2->vertex->name));
}

int			ft_newlink(t_vertex *v1, t_vertex *v2)
{
	t_route	route;

	route.vertex = v2;
	route.flow = 0;
	if (ft_lstfind(v1->link, &route, ft_routecmp))
	{
		ft_warning(1, "route already exists");
		return (0);
	}
	ft_lstadd(&(v1->link), ft_lstnew(&route, sizeof(route)));
	return (1);
}
