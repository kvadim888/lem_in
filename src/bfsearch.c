/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfsearch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:35:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/03/02 19:35:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_list	*ft_linkdup(t_vertex *vertex)
{
	t_vertex	*root;
	t_list		*lst;
	t_list		*new;

	new = NULL;
	lst = vertex->link;
	while (lst)
	{
		if (((t_route *)lst->content)->flow < 1)
		{
			root = ((t_route *)lst->content)->vertex->root;
			((t_route *)lst->content)->vertex->root = (root) ? root : vertex;
			ft_lstadd(&new, ft_lstnew(lst->content, lst->content_size));
		}
		lst = lst->next;
	}
	return (new);
}

static t_list	*ft_dequeue(t_list *queue)
{
	t_list	*q;

	q = (queue) ? queue->next : NULL;
	ft_lstdelone(&queue, ft_lstrm);
	return (q);
}

static t_list	*ft_shortestpath(t_graph *graph)
{
	t_list		*path;
	t_vertex	*vertex;

	path = NULL;
	vertex = graph->end;
	while (vertex)
	{
		ft_lstadd(&path, ft_lstnew(vertex, 0));
		vertex = vertex->root;
	}
	if (path && (path->content != graph->start))
		ft_lstdel(&path, NULL);
	return (path);
}

t_list			*ft_bfs(t_graph *graph)
{
	t_list		*queue;
	t_route		*tmp;

	queue = NULL;
	ft_lstappend(&queue, ft_linkdup(graph->start));
	while (queue)
	{
		tmp = (t_route *)queue->content;
		if (tmp->vertex->status == 0)
			ft_lstappend(&queue, ft_linkdup(tmp->vertex));
		if (tmp->vertex == graph->end)
			break ;
		queue = ft_dequeue(queue);
	}
	graph->start->root = NULL;
	ft_lstdel(&queue, ft_lstrm);
	return (ft_shortestpath(graph));
}
