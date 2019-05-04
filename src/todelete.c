/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todelete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:01:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/02 15:01:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

# define NORM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GREEN  "\x1B[32m"
# define YELLOW  "\x1B[33m"
# define BLUE  "\x1B[34m"
# define MAGENTA  "\x1B[35m"
# define CYAN  "\x1B[36m"
# define WHITE  "\x1B[37m"

void	ft_vertexshow(t_list *lst)
{
	t_vertex	*vertex;

	vertex = lst->content;
	printf("%s(%d)%s[%s]%s[%s]%s:",
		   CYAN, vertex->status, BLUE, vertex->name,
		   GREEN, (vertex->root) ? vertex->root->name : NULL, NORM);
	fflush(stdout);
	if (vertex->link)
		ft_lstiter(vertex->link, ft_linkshow);
	else
		ft_printf("[null]\n");
}

void	ft_linkshow(t_list *lst)
{
	t_route	*route;

	if (lst->content)
	{
		route = lst->content;
		ft_printf("[%d|'%s']->", route->flow, route->vertex->name);
	}
	if (lst->next == NULL)
		ft_printf("[null]\n");
}

void	ft_pathshow(t_list *lst)
{
	if (lst->content)
		ft_printf("[%s; %d]", ((t_vertex *)lst->content)->name, ((t_vertex *)lst->content)->status);
	if (lst->next)
		ft_printf("->");
	else
		ft_printf("\n");
}

void	ft_antshow(t_list *lst)
{
	t_ant	*ant;
	char	*room;

	ant = lst->content;
	if (!ant)
		return;
	room = ((ant->room) && ant->room->content) ? ((t_vertex*)ant->room->content)->name : "[none]";
	ft_printf("ant[#%d]:[%s] ", ant->number, room);
}
