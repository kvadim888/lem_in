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

int		main(int ac, char **av)
{
	int			fd;
	int			ants;
	t_graph		graph;

	fd = open(av[ac - 1], O_RDONLY);
	graph = (t_graph){NULL, NULL, NULL};
	ft_readfile(fd, &graph, &ants);
	ft_printf("ants = %d\n", ants);
	if (ants == 0)
	{
		ft_dprintf(2, "ERROR\n");
		return (1);
	}
	ft_lstiter(graph.head, ft_vertexshow);
	ft_edkarp(&graph);
	ft_lstiter(graph.head, ft_vertexshow);
//	ft_lemin(&graph,ants);
//	system("leaks lem-in");
	return (0);
}
