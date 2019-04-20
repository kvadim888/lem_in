/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:32:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:32:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

void 		ft_linkreduce(t_list *vert_lst)
{
	t_list	*prev;
	t_list	*tmp;
	t_list	*link;

	prev = NULL;
	link = ((t_vertex *)vert_lst->content)->link;
	while (link)
	{
		if (((t_route *)link->content)->flow != 1)
		{
			tmp = link;
			link = link->next;
			ft_lstdelone(&tmp, ft_lstrm);
			if (prev)
				prev->next = link;
			else
				((t_vertex *)vert_lst->content)->link = link;
		}
		else
		{
			prev = link;
			link = link->next;
		}
	}
}

void		ft_bfsreset(t_list *vertex)
{
	if (vertex)
	{
		((t_vertex *)vertex->content)->status = 0;
		((t_vertex *)vertex->content)->root = NULL;
	}
}

void		ft_edkarp(t_graph *graph)
{
	t_list		*path;

	while ((path = ft_bfs(graph)) != NULL)
	{
		ft_lstiter(path, ft_addflow);
		ft_lstiter(graph->head, ft_bfsreset);
        ft_lstdel(&path, ft_lstrm);
	}
	ft_lstiter(graph->head, ft_linkreduce);
}
