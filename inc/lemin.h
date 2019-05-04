/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 11:00:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/02/01 11:00:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define ERR_ANTS	"Incorrect ants amount"
# define ERR_READ	"File can not be read"
# define ERR_FROOM	"Incorrect room format"
# define ERR_FLINK	"Incorrect link format"
# define ERR_DVERT	"Duplicate vertices are exist"
# define ERR_LINK	"Links does not belong to existing vertices"
# define ERR_UNFILL	"Unable to fill the graph"
# define ERR_UNLINK	"Unable to link the graph"
# define ERR_EMPTY	"The graph is empty"
# define ERR_START	"The start label does not exist"
# define ERR_END	"The end label does not exist"
# define ERR_NOWAY	"There is no path from start to end"

typedef struct		s_vertex
{
	char			*name;
	int				status;
	int				x;
	int				y;
	t_list			*link;
	struct s_vertex	*root;
}					t_vertex;

typedef	struct		s_graph
{
	t_list			*head;
	t_vertex		*start;
	t_vertex		*end;
}					t_graph;

typedef struct		s_route
{
	struct s_vertex	*vertex;
	int				flow;
}					t_route;

typedef struct		s_ant
{
	struct s_list	*room;
	int				number;
}					t_ant;

typedef struct		s_solving
{
	size_t			maxlen;
	t_list			*path;
	int				branches;
	int				steps;
}					t_solving;

int					ft_readfile(int fd, t_graph *graph, int *ants);
void				ft_readvertex(char *str, t_vertex *vertex);
int					ft_newlink(t_vertex *v1, t_vertex *v2);
int					ft_linkvertex(t_graph *graph, char *name1, char *name2);

int					ft_islabel(char *str);
int					ft_iscomment(char const *str);
int					ft_islink(char *str);
int					ft_isnumber(char *num);

void				ft_error(int trigger, char const *msg);
void				ft_warning(int trigger, char const *msg);

t_list				*ft_bfs(t_graph *graph);
void				ft_bfsreset(t_list *vertex);

void				ft_addflow(t_list *link);

void				ft_printline(t_list *lst);
void				ft_lemin(t_list *path, int num);
t_solving			*ft_newsolving(t_graph *graph, int ants);
int					ft_simulate(t_graph *graph);
t_list				*ft_solver(t_graph *graph, int ants);

//todo delete functions from project
void				ft_vertexshow(t_list *lst);
void				ft_linkshow(t_list *lst);
void				ft_pathshow(t_list *lst);
void				ft_antshow(t_list *lst);

#endif
