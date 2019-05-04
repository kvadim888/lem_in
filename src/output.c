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
	t_ant		*ant;

	if (!lst->content)
		return;
	ant = lst->content;
	if (!(ant->room && ant->room->content))
		return ;
	ft_printf("L%d-%s ", ant->number, ((t_vertex *)ant->room->content)->name);
}

static int		ft_moveant(t_ant *ant, t_list **path)
{
	t_list	*next_room;

	if (ant->room)
		next_room = ant->room->next;
	else
	{
		next_room = (*path)->content;
		*path = (*path)->next;
	}
	if (!next_room)
		return (0);
	if (!(next_room->next) || ((t_vertex *)next_room->content)->status < 1)
	{
		if (ant->room)
			((t_vertex *)ant->room->content)->status--;
		ant->room = next_room;
		((t_vertex *)ant->room->content)->status++;
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

void			ft_lemin(t_list *path, int num)
{
	t_list	*lstant;

	lstant = ft_ants(num);
	while (!ft_step(&path, lstant))
	{
		ft_lstiter(lstant, ft_printstep);
		ft_putchar('\n');
	}
	ft_lstdel(&lstant, ft_lstrm);
}
