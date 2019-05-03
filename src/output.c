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

static void		ft_printstep(t_list *lst)
{
	char		delim;
	t_ant		*ant;

	if (!lst->content)
		return;
	ant = lst->content;
	if (ant->room)
	{
		delim = (lst->next) ? ' ' : '\0';
		if (ant->room->content)
			ft_printf("L%d-%s ", ant->number,
					 ((t_vertex *)ant->room->content)->name, delim);
	}
}

//todo refactor to one case
static int		ft_moveant(t_ant *ant, t_list **path)
{
	t_list	*next_room;
	t_list	*start;

	if (ant->room == NULL)
	{
		start = (*path)->content;
		if (((t_vertex *)start->content)->status < 1)
		{
			ant->room = (*path)->content;
			((t_vertex *)ant->room->content)->status++; /* enter the next room */
			*path = (*path)->next;
		}
		return (1);
	}
	if (ant->room->next == NULL)
		return (0);
	next_room = ant->room->next;
	if ((next_room->next == NULL) || /* end room */
		  (((t_vertex *)next_room->content)->status < 1)) /* mid room */
	{
		((t_vertex *)ant->room->content)->status--; /* leave the room */
		ant->room = next_room;
		((t_vertex *)ant->room->content)->status++; /* enter the next room */
	}
	return (1);
}

static int		ft_step(t_list **path, t_list *antlist)
{
	int		finish;

	finish = 1;
	while (antlist)
	{
		if (antlist->content)
		{
			if (!ft_moveant(antlist->content, path))
			{
				ft_lstrm(antlist->content, antlist->content_size);
				antlist->content = NULL;
				antlist->content_size = 0;
			}
			finish = 0;
		}
		antlist = antlist->next;
	}
	return (finish);
}

void			ft_lemin(t_graph *graph, t_list *path, int num)
{
	t_list	*antlist;
	int		steps = 0;//todo delete variable

	antlist = ft_ants(num);
	while (!ft_step(&path, antlist))
	{
		ft_lstiter(antlist, ft_printstep);
		ft_printf("\n");
		steps++;
	}
	ft_lstdel(&antlist, ft_lstrm);
}
