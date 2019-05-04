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
	t_list		*path;

	graph = (t_graph){.head = NULL, .start = NULL, .end = NULL};
	fd = open(av[ac - 1], O_RDONLY);
	ft_error((fd < 0), "Can not open file");
	ft_readfile(fd, &graph, &ants);
	path = ft_solver(&graph, ants);
	ft_lemin(path, ants);
	return (0);
}
