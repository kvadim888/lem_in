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

int			ft_readants(int fd, char **str)
{
	int		ants;
	int		i;

	if ((get_next_line(fd, str) < 0) || ft_strlen(*str) == 0)
		return (0);
	i = 0;
	while (ft_isdigit((*str)[i]))
		i++;
	ants = (i == ft_strlen(*str)) ? ft_atoi(*str) : 0;
	ft_printf("ft_readants>%s\n",*str);
	ft_strdel(str);
	return (ants);
}

int	ft_cmp(void const *vertex1, void const *vertex2)
{
	t_vertex const *v1;
	t_vertex const *v2;

	v1 = vertex1;
	v2 = vertex2;
	ft_printf("{%s},{%s}", v1->name, v2->name);
	if (ft_strequ(v1->name, v2->name))
		return (1);
	if ((v1->x == v2->x) && (v1->y == v2->y))
		return (1);
	return (0);
}

int 		ft_fillgraph(t_graph *graph, int fd, char **str)
{
	t_vertex	vertex;
	int			label;

	label = 0;
	while ((get_next_line(fd, str) > 0) && !(ft_islink(*str)))
	{
		ft_printf("ft_fillgraph>%s\n",*str);
		if (**str != '#')
		{
			ft_readvertex(*str, &vertex);
			ft_printf("{%s;%d;%d}\n",vertex.name, vertex.x, vertex.y);
			if (ft_lstfind(graph->head, &vertex, ft_cmp))
			{
				ft_error("vertex is not unique");
				ft_strdel(str);
			}
			ft_printf("{%s;%d;%d}\n",vertex.name, vertex.x, vertex.y);
			ft_lstadd(&(graph->head), ft_lstnew(&vertex, sizeof(t_vertex)));
			ft_vertexshow(graph->head);
			if (label == 1)
				graph->start = graph->head->content;
			if (label == 2)
				graph->end = graph->head->content;
			label = 0;
		}
		else
			label = (label == 0) ? ft_label(*str) : label;
		ft_strdel(str);
	}
	return (1);
}

int 		ft_linkgraph(t_graph *graph, int fd, char **str)
{
	char	*name1;
	char	*name2;
	int		stat;

	while (*str)
	{
		ft_printf("ft_linkgraph>%s\n",str);
		if (**str != '#')
		{
			if (!ft_islink(*str))
				return (0);
			name1 = ft_strsub(*str, 0, ft_strchr(*str, '-') - *str);
			name2 = ft_strchr(*str, '-') + 1;
			stat = ft_linkvertex(graph, name1, name2);
			ft_strdel(&name1);
			if (stat == 0)
				return (0);
		}
		ft_strdel(str);
		if (get_next_line(fd, str) < 1)
			return (1);
	}
	return (0);
}

int			ft_readfile(t_graph *graph, int fd)
{
	int		stat;
	char	*str;
	int		ants;

	if ((ants = ft_readants(fd, &str)) == 0)
		ft_error(ANTS);
	if ((stat = ft_fillgraph(graph, fd, &str)) == 1)
		stat = ft_linkgraph(graph, fd, &str);
	//TODO: check begin and end
	//TODO: check link between begin and end
	ft_strdel(&str);
	return ((stat) ? ants : 0);
}

void ft_error(char const *msg)
{
	ft_dprintf(2, "ERROR: %s\n", msg);
	exit(0);
}
