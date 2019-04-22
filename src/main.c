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

	graph = (t_graph){NULL, NULL, NULL};
	fd = open(av[ac - 1], O_RDONLY);
	ft_error((fd < 0), "Can not open file");
	ft_readfile(fd, &graph, &ants);
	ft_printf("Map was readed\n");
	ft_lstiter(graph.head, ft_vertexshow);
	ft_edkarp(&graph);
	ft_lstiter(graph.head, ft_vertexshow);
	ft_lemin(&graph,ants);
//	system("leaks lem-in");
	return (0);
}
