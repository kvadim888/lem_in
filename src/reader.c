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

int 		ft_fillgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	vertex;
	int			label;

	label = 0;
	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		vertex = (t_vertex){.name = NULL, .x = 0, .y = 0, .status = 0,
							.link = NULL, .root = NULL};
		if (ft_iscomment(*str))
		{
			label = (label == 0) ? ft_label(*str) : label;
			continue;
		}
		ft_readvertex(*str, &vertex);
		ft_error((ft_lstfind(graph->head, &vertex, ft_vertexcmp) != NULL),
				ERR_UNIQUE);
		ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
		if (label)
			ft_setlabel(graph, graph->head->content, label);
		label = 0;
		ft_strdel(str);
	}
	return (0);
}

int 	ft_linkgraph(t_graph *graph, int fd, char **str)
{
	char	*delim;

	while (*str && **str)
	{
		if (ft_iscomment(*str))
		{
			ft_strdel(str);
			continue;
		}
		ft_error(!ft_islink(*str), ERR_INVALID_LINK);
		delim = ft_strchr(*str, '-');
		*delim = '\0';
		ft_printf("[%s][%s]",*str, delim + 1);
		ft_error(!ft_linkvertex(graph, *str, delim + 1), "ft_linkvertex");
		ft_strdel(str);
		get_next_line(fd, str);
	}
	return (0);
}

int		ft_readfile(int fd, t_graph *graph, int *ants)
{
	char	*str;

	ft_error((get_next_line(fd, &str) < 0), ERR_READ);
	ft_error(!ft_isnumber(str), ERR_ANTS);
	*ants = ft_atoi(str);
	ft_error(ft_fillgraph(graph, fd, &str), ERR_FILLGRAPH);
	ft_error(ft_linkgraph(graph, fd, &str), ERR_LINKGRAPH);
	ft_error((graph->head == NULL), ERR_EMTPY_GRAPH);
	ft_error((graph->start == NULL), ERR_NOSTART);
	ft_error((graph->end == NULL), ERR_NOEND);
	ft_error((ft_bfs(graph) == NULL), ERR_SE_LINK);
	ft_strdel(&str);
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
