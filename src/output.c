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
	static char	delim = '\0';
	t_ant		*ant;

	ant = lst->content;
	if (ant && (ant->room->content != NULL) &&
		(ant->room->content != graph->start))
	{
		ft_printf("L%d-%s%c", ant->number,
				((t_vertex *)ant->room->content)->name, delim);
		delim = ' ';
	}
	delim = (lst->next) ? delim : 0;
}

static void		ft_moveant(t_list *antlist, t_list **path)
{
	t_ant	*ant;
	t_list	*next_room;

	ant = antlist->content;
	if (ant->room == NULL)
	{
		ant->room = (*path)->content;
		*path = (*path)->next;
	}
	else
	{
		next_room = ant->room->next;
		if (next_room == NULL)
			ft_memdel((void **)&antlist->content);
		else if (next_room->next == NULL ||
				 ((t_vertex *)next_room->content)->status < 1)
		{
			antlist->content = next_room;
			((t_vertex *)next_room->content)->status++;
		}
	}
}

static int		ft_step(t_list *path, t_list *antlist)
{
	if (!antlist)
		return (0);
	while (antlist)
	{
		if (antlist->content)
			ft_moveant(antlist, &path);
		antlist = antlist->next;
	}
	return (1);
}

void			ft_lemin(t_graph *graph, t_list *path, int num)
{
	t_list	*ants;
	t_list	*tmp;
	int		steps = 0;

	ants = ft_ants(num);
	while (ft_step(path, ants))
	{
		tmp = ants;
		while (tmp)
		{
			ft_printstep(tmp, graph);
			tmp = tmp->next;
		}
		steps++;
	}
	ft_lstdel(&ants, ft_lstrm);
	ft_printf("steps = %d\n", steps);
}
