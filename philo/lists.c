/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:04:09 by idouni            #+#    #+#             */
/*   Updated: 2023/01/24 14:04:38 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_list	*ft_lstnew(t_data data)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = (t_list *)h_malloc(data, sizeof(t_list), new_node);
	if (new_node)
	{
		new_node->next = NULL;
	}
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	if (lst == NULL)
		return (NULL);
	node = lst;
	while (lst != NULL)
	{
		node = lst;
		lst = lst->next;
	}
	return (node);
}

void	ft_lstadd_back(t_data data, t_list **lst, t_list *new)
{
	t_list	*o_last;

	if (new == NULL)
	{
		new = ft_lstnew(data);
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	o_last = ft_lstlast(*lst);
	o_last->next = new;
	new->next = NULL;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*node;
	t_list	*n_node;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		n_node = node->next;
		free(node);
		node = n_node;
	}
	*lst = NULL;
}

t_list	*search_by_id(int id, t_data data)
{
	static t_data data2;
	t_list	*n;

	if (data.head)
		data = data2;
	n = data.head;
	if (!n)
		ft_exit_with_error(data);
	while (n)
	{
		if (id == n->philosopher_id)
			return (n);
		n = n->next;
	}
	return (n);
}