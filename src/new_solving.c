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
	lst = vertex->link;
	while ((lst = ft_lstfind(lst, &flow, ft_flowcmp)) != NULL)
	{
		ft_lstappend(&tail, ft_lstnew(((t_route *)lst->content)->vertex, 0));
		tail = tail->next;
		lst = ((t_route *)lst->content)->vertex->link;
	}
	ft_printf("\x1B[31m branch: \x1B[0m"); ft_lstiter(branch, ft_pathshow); //todo delete
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
			ft_lstadd(&path, ft_lstnew(branch, 0));
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
		len = ft_lstlen(path->content);
		if ((len == 0) || (solving->maxlen < len))
			solving->maxlen = len;
		solving->branches++;
		path = path->next;
	}
	solving->steps = solving->maxlen + ants / solving->branches;
	return (solving);
}
