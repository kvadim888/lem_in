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

void				ft_error(int trigger, char const *msg);
void				ft_warning(int trigger, char const *msg);

int					ft_linkvertex(t_graph *graph, char *name1, char *name2);
int					ft_newlink(t_vertex *v1, t_vertex *v2);

int					ft_readfile(int fd, t_graph *graph, int *ants);

/*
** flow_calculation.c
*/

void				ft_addflow(t_list *link);

/*
** bfsearch.c
*/

t_list				*ft_bfs(t_graph *graph);
void				ft_bfsreset(t_list *vertex);

/*
** validator.c
*/

int					ft_label(char *str);
int					ft_isnumber(char *num);
int					ft_islink(char *str);

/*
**	reader.c
*/

void				ft_readvertex(char *str, t_vertex *vertex);

void				ft_lemin(t_graph *graph, t_list *path, int num);


/*
 *  solver.c
 */
void		ft_addflow(t_list *link);
void		ft_bfsreset(t_list *vertex);
t_solving	*ft_newsolving(t_graph *graph, int ants);
int			ft_simulate(t_graph *graph);
t_list		*ft_solver(t_graph *graph, int ants);


/*
 *  TODELETE -- additional functions for convenience
 */

void				ft_vertexshow(t_list *lst);
void				ft_linkshow(t_list *lst);
void				ft_pathshow(t_list *lst);

#endif
