/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:33:10 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:23 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_showpath(t_list *lst)
{
	t_vertex	*vertex;

	vertex = (t_vertex *)lst->content;
	if (vertex)
		ft_printf("[%s]", vertex->name);
}

int		main(int ac, char **av)
{
	int			fd;
	int			ants;
	t_graph		graph;

	graph = (t_graph){NULL, NULL, NULL};
	fd = open(av[ac - 1], O_RDONLY);
	ft_error((fd < 0), "Can not open file");
	ft_readfile(fd, &graph, &ants);
//	ft_lstiter(graph.head, ft_vertexshow);
//	t_list *path = ft_bfs(&graph);
//	ft_lstiter(path, ft_showpath);
//	ft_lstiter(graph.head, ft_vertexshow);
	ft_solver(&graph, ants);
	ft_lemin(&graph, ants);
//	system("leaks lem-in");
	return (0);
}
