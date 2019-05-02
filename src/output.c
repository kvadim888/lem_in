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

static t_list	*ft_ants(int num)
{
	t_list	*ants;

	ants = NULL;
	while (num > 0)
		ft_lstadd(&ants, ft_lstnew(&(t_ant){NULL, num--}, sizeof(t_ant)));
	return (ants);
}

static void		ft_printstep(t_list *lst, t_graph *graph)
{
	char		delim;
	t_ant		*ant;

	ant = lst->content;
	if (ant && (ant->room->content != NULL) &&
		(ant->room->content != graph->start))
	{
		delim = (lst->next) ? ' ' : '\0';
		ft_printf("L%d-%s ", ant->number,
				((t_vertex *)ant->room->content)->name, delim);
	}
}

static void		ft_moveant(t_ant **ant, t_list **path)
{
	t_list	*next_room;

	/* put ants in start room*/
	if ((*ant)->room == NULL)
	{
		(*ant)->room = (*path)->content;
		*path = (*path)->next;
	}
	/* continue ants moving */
	else
	{
		next_room = (*ant)->room->next;
		if (next_room == NULL)
			ft_memdel((void **)ant);
		else if (next_room->next == NULL || /* end room */
				 ((t_vertex *)next_room->content)->status < 1) /* mid room */
		{
			(*ant)->room = next_room;
			((t_vertex *)next_room->content)->status++;
		}
	}
}

static int		ft_step(t_list **path, t_list *antlist)
{
	if (!antlist)
		return (0);
	while (antlist)
	{
		if (antlist->content)
			ft_moveant((t_ant **)&(antlist->content), path);
		antlist = antlist->next;
	}
	return (1);
}

void			ft_lemin(t_graph *graph, t_list *path, int num)
{
	t_list	*antlist;
	t_list	*tmp;
	int		steps = 0;

	antlist = ft_ants(num);
	while (ft_step(&path, antlist))
	{
		tmp = antlist;
		while (tmp)
		{
			ft_printf("new step\n");
			ft_printstep(tmp, graph);
			tmp = tmp->next;
		}
		steps++;
	}
	ft_lstdel(&antlist, ft_lstrm);
	ft_printf("steps = %d\n", steps);
}
