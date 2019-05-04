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

static int	ft_vertexcmp(void const *vertex1, void const *vertex2)
{
	t_vertex const	*v1;
	t_vertex const	*v2;

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

int			ft_fillgraph(t_graph *graph, int fd, char **str, t_list **map)
{
	t_vertex	vertex;
	int			label;

	label = 0;
	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		ft_lstappend(map, ft_lstnew(*str, 0));
		*map = (*map)->next;
		vertex = (t_vertex){.name = NULL, .x = 0, .y = 0, .status = 0,
							.link = NULL, .root = NULL};
		if (ft_iscomment(*str))
			label = (label == 0) ? ft_islabel(*str) : label;
		else
		{
			ft_readvertex(*str, &vertex);
			ft_error((ft_lstfind(graph->head, &vertex, ft_vertexcmp) != NULL),
					 ERR_DVERT);
			ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
			if (label)
				ft_setlabel(graph, graph->head->content, label);
			label = 0;
		}
	}
	return (0);
}

int			ft_linkgraph(t_graph *graph, int fd, char **str, t_list **map)
{
	char	*delim;

	while (*str && **str)
	{
		if (!ft_iscomment(*str))
		{
			ft_error(!ft_islink(*str), ERR_FLINK);
			delim = ft_strchr(*str, '-');
			*delim = '\0';
			ft_error(!ft_linkvertex(graph, *str, delim + 1), ERR_FLINK);
			*delim = '-';
		}
		ft_lstappend(map, ft_lstnew(*str, 0));
		*map = (*map)->next;
		get_next_line(fd, str);
	}
	return (0);
}

int			ft_readfile(int fd, t_graph *graph, int *ants)
{
	char	*str;
	t_list	*head;
	t_list	*lst;

	head = NULL;
	while (get_next_line(fd, &str) >= 0 && ft_iscomment(str))
		ft_lstappend(&head, ft_lstnew(str, 0));
	*ants = ft_atoi(str);
	ft_error(!ft_isnumber(str) || *ants <= 0, ERR_ANTS);
	ft_lstappend(&head, ft_lstnew(str, 0));
	lst = head;
	ft_error(ft_fillgraph(graph, fd, &str, &lst), ERR_UNFILL);
	ft_error(ft_linkgraph(graph, fd, &str, &lst), ERR_UNLINK);
	ft_error((graph->head == NULL), ERR_EMPTY);
	ft_error((graph->start == NULL), ERR_START);
	ft_error((graph->end == NULL), ERR_END);
	ft_error((lst = ft_bfs(graph)) == NULL, ERR_NOWAY);
	ft_lstdel(&lst, ft_lstrm);
	ft_strdel(&str);
	ft_lstiter(head, ft_printline);
	ft_lstdel(&head, ft_lstrm);
	return (0);
}
