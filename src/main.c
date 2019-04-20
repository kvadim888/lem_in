/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:33:10 by vkryvono          #+#    #+#             */
/*   Updated: 2019/01/31 18:33:23 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*ft_vertexcopy(t_list *lst)
{
	return (ft_lstnew(lst->content, lst->content_size));
}

//int		main(int ac, char **av)
//{
//	int			fd;
//	int			ants;
//	t_graph		graph;
//
//	fd = open(av[1], O_RDONLY);
//	ants = ft_readfile(&graph, fd);
//	ft_printf("ants = %d\n", ants);
//	if (ants == 0)
//	{
//		ft_dprintf(2, "ERROR\n");
//		return (1);
//	}
//	ft_lstiter(graph.head, ft_vertexshow);
//	ft_edkarp(&graph);
//	ft_lstiter(graph.head, ft_vertexshow);
////	ft_lemin(&graph,ants);
////	system("leaks lem-in");
//	return (0);
//}

void  ft_show(t_list *lst)
{
	ft_printf("{%s, %zu}", lst->content, lst->content_size);
}

int	ft_cmpname(void const *data1, void const *data2)
{
	return ft_strequ((char const *)data1, (char const *)data2);
}

int main()
{
	t_list *head;

	ft_lstadd(&head, &(t_list){"hello1", sizeof("hello1"), NULL});
	ft_lstappend(&head, &(t_list){"hello2", sizeof("hello2"), NULL});
	ft_lstadd(&head, &(t_list){"hello3", sizeof("hello3"), NULL});
	ft_lstappend(&head, &(t_list){"hello4", sizeof("hello3"), NULL});
	ft_lstiter(head, ft_show);
	t_list *str = ft_lstfind(head, "hello1", ft_cmpname);
	ft_lstiter(str, ft_show);
	return 0;
}
