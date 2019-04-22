/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:59:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 10:59:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

static int	ft_vertexcmp(void const *vertex1, void const *vertex2)
{
	t_vertex const *v1;
	t_vertex const *v2;

	v1 = vertex1;
	v2 = vertex2;
	if (ft_strequ(v1->name, v2->name))
		return (1);
	if ((v1->x == v2->x) && (v1->y == v2->y))
		return (1);
	return (0);
}

void		ft_setlabel(t_graph *graph, t_vertex *vertex, int label)
{
	if (label == 1)
		graph->start = vertex;
	if (label == 2)
		graph->end = vertex;
}

int			ft_iscomment(char const *str)
{
	return ((str != NULL) && (*str == '#'));
}

int ft_fillgraph(t_graph *graph, int fd, char **str, t_list **map)
{
	t_vertex	vertex;
	int			label;

	label = 0;
	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		vertex = (t_vertex){.name = NULL, .x = 0, .y = 0, .status = 0,
							.link = NULL, .root = NULL};
		if (ft_iscomment(*str))
			label = (label == 0) ? ft_label(*str) : label;
		else
		{
			ft_readvertex(*str, &vertex);
			ft_error((ft_lstfind(graph->head, &vertex, ft_vertexcmp) != NULL),
					 "Vertex is not unique");
			ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
			if (label)
				ft_setlabel(graph, graph->head->content, label);
			label = 0;
		}
		ft_lstappend(map, ft_lstnew(*str, 0));
		*map = (*map)->next;
		printf("[%zu|%s]", (*map)->content_size, (*map)->content);
	}
	return (0);
}

int ft_linkgraph(t_graph *graph, int fd, char **str, t_list **map)
{
	char	*delim;

	while (*str && **str)
	{
		if (!ft_iscomment(*str))
		{
			ft_error(!ft_islink(*str), "Invalid links");
			delim = ft_strchr(*str, '-');
			*delim = '\0';
			ft_error(!ft_linkvertex(graph, *str, delim + 1), "ft_linkvertex");
		}
		ft_lstappend(map, ft_lstnew(*str, 0));
		*map = (*map)->next;
		printf("[%zu|%s]", (*map)->content_size, (*map)->content);
		get_next_line(fd, str);
	}
	return (0);
}

void	ft_printline(t_list *lst)
{
	write(1, lst->content, ft_strlen(lst->content));
	write(1, "\n", 1);
}

int		ft_readfile(int fd, t_graph *graph, int *ants)
{
	char	*str;
	t_list	*head;
	t_list	*lst;

	head = NULL;
	ft_error((get_next_line(fd, &str) < 0), "File reading error");
	ft_error(!ft_isnumber(str), "Invalid amount of ants");
	*ants = ft_atoi(str);
	ft_lstappend(&head, ft_lstnew(str, 0));
	lst = head;
	ft_error(ft_fillgraph(graph, fd, &str, &lst), "Unable to fill graph");
	ft_error(ft_linkgraph(graph, fd, &str, &lst), "Unable to link graph");
	ft_error((graph->head == NULL), "Empty graph");
	ft_error((graph->start == NULL), "Start label doesn't exist");
	ft_error((graph->end == NULL), "End label doesn't exist");
	ft_error((ft_bfs(graph) == NULL), "Link between start and end doesn't exist");
	ft_strdel(&str);
	ft_printf("reading done\n");
	ft_lstiter(head, ft_printline);
	ft_lstdel(&head, ft_lstrm);
	return (0);
}

void	ft_error(int trigger, char const *msg)
{
	if (trigger)
	{
		ft_dprintf(2, "ERROR: %s\n", msg);
		exit(0);
	}
}

void	ft_warning(int trigger, char const *msg)
{
	if (trigger)
		ft_dprintf(2, "WARNING: %s\n", msg);
}
