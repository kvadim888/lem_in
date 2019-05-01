/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_solving.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:32:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_flowcmp(void const *route, void const *flow)
{
	return (((t_route const *)route)->flow == *(int*)flow);
}

static t_list	*ft_newbranch(t_vertex *vertex)
{
	t_list	*lst;
	t_list	*branch;
	t_list	*tail;
	int		flow;

	flow = 1;
	branch = ft_lstnew(vertex, 0);
	tail = branch;
	while ((lst = ft_lstfind(vertex->link, &flow, ft_flowcmp)) != NULL)
	{
		ft_lstappend(&tail, ft_lstnew(((t_route *)lst->content)->vertex, 0));
		tail = tail->next;
	}
	return (branch);
}

static t_list	*ft_newpath(t_graph *graph)
{
	t_list	*path;
	t_list	*link;
	t_list	*branch;

	path = NULL;
	link = graph->start->link;
	while (link)
	{
		if (((t_route *)link->content)->flow == 1)
		{
			branch = ft_newbranch(((t_route *)link->content)->vertex);
			ft_lstadd(&branch, &(t_list){graph->start, 0, NULL});
			ft_lstadd(&path, &(t_list){branch, 0, NULL});
		}
		link = link->next;
	}
	return (path);
}

t_solving		*ft_newsolving(t_graph *graph, int ants)
{
	t_list		*path;
	t_solving	*solving;
	size_t		len;

	solving = ft_memalloc(sizeof(t_solving));
	path = ft_newpath(graph);
	solving->path = path;
	solving->maxlen = 0;
	solving->branches = 0;
	while (path)
	{
		len = ft_lstlen(path->content) - 1;
		if ((len == 0) || (solving->maxlen < len))
			solving->maxlen = len;
		solving->branches++;
		path = path->next;
	}
	solving->steps = solving->maxlen + ants / solving->branches;
	return (solving);
}
