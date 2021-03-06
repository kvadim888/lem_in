/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:55:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/04 19:55:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_printstep(t_list *lst, t_graph *graph)
{
	static char	delim = '\0';
	t_ant		*ant;

	ant = lst->content;
	if (ant && (ant->vertex != NULL) && (ant->vertex != graph->start))
	{
		ft_printf("L%d-%s%c", ant->number, ant->vertex->name, delim);
		delim = ' ';
	}
	delim = (lst->next) ? delim : 0;
}

static int		ft_moveants(t_graph *graph, t_list *ant)
{
	int			status;
	t_list		*link;
	t_vertex	*vertex;

	link = graph->start->link;
	status = 0;
	while (ant)
	{
		vertex = ((t_ant *)ant->content)->vertex;
		if (vertex)
		{
			if (vertex != graph->start)
				((t_ant *)ant->content)->vertex = (vertex->link)
					  ? ((t_route *)vertex->link->content)->vertex : NULL;
			else if (link)
			{
				((t_ant *)ant->content)->vertex
									= ((t_route *)link->content)->vertex;
				link = (link->next) ? link->next : NULL;
			}
		}
		status += (((t_ant *)ant->content)->vertex) ? 1 : 0;
		ant = ant->next;
	}
	return (status);
}

void		ft_lemin(t_graph *graph, int num)
{
	t_list	*ants;
	t_list	*tmp;
	int		i = 0;

	ants = NULL;
	while (num > 0)
		ft_lstadd(&ants, ft_lstnew(&(t_ant){graph->start, num--}, sizeof(t_ant)));
	while (ft_moveants(graph, ants))
	{
		tmp = ants;
		while (tmp)
		{
			ft_printstep(tmp, graph);
			tmp = tmp->next;
		}
		ft_printf("|\n");
		i++;
	}
	ft_lstdel(&ants, ft_lstrm);
	ft_printf("steps = %d\n", i);
}
