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

static void			ft_rmbranch(void *content, size_t size)
{
	t_list	*branch;

	branch = content;
	ft_lstdel(&branch, ft_lstrm);
	if (content && size > 0)
		free(content);
}

static void			ft_rmsolving(void *content, size_t size)
{
	t_list	*path;

	if (content || size > 0)
	{
		path = ((t_solving *)content)->path;
		ft_lstdel(&path, ft_rmbranch);
		free(content);
	}
}

static t_solving	*ft_optimal(t_list *routes)
{
	t_list		*lst;
	t_list		*tmp;
	t_solving	*solving;

	tmp = routes;
	lst = routes->next;
	while (lst)
	{
		if (((t_solving *)lst->content)->steps
			< ((t_solving *)tmp->content)->steps)
			tmp = lst;
		lst = lst->next;
	}
	solving = tmp->content;
	tmp->content = NULL;
	tmp->content_size = 0;
	ft_lstdel(&routes, ft_rmsolving);
	return (solving);
}

t_list				*ft_solver(t_graph *graph, int ants)
{
	t_solving	*solving;
	t_list		*routes;
	t_list		*bfs;

	routes = NULL;
	solving = NULL;
	while ((bfs = ft_bfs(graph)) != NULL)
	{
		ft_printf("new bfs (len = %zu): ", ft_lstlen(bfs)); //todo delete line
		ft_lstiter(bfs, ft_pathshow); //todo delete line
		ft_lstiter(bfs, ft_addflow);
		ft_lstiter(graph->head, ft_bfsreset); // reset
		if (ft_simulate(graph))
		{
			solving = ft_newsolving(graph, ants);
			if (solving->steps == 0)
				break ;
			ft_lstadd(&routes, ft_lstnew(solving, 0));
		}
		ft_lstiter(graph->head, ft_bfsreset); // reset after simulation
		ft_lstdel(&bfs, ft_lstrm);
	}
	solving = (routes) ? ft_optimal(routes) : solving;
	routes = (solving) ? solving->path : NULL;
	ft_memdel((void **)&solving);
	if (routes)
		ft_lsttail(routes)->next = routes;
	return (routes);
}
