/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:25:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/22 11:11:38 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exibe a lista
void	ft_lstdisplay(t_list *lst)
{
	if (!lst)
		return ;
	printf("%s\n", (char *)lst->content);
	if (lst->next)
		ft_lstdisplay(lst->next);
}

void	ft_lstremove(t_list **lst, char *value)
{
	t_list	*var_node;
	t_list	*temp;

	temp = *lst;
	var_node = ft_lstfind(*lst, value);
	if (!var_node)
		return ;
	if (temp == var_node)
	{
		*lst = (*lst)->next;
		ft_lstdelone(var_node, free);
		return ;
	}
	while (temp->next != var_node)
		temp = temp->next;
	temp->next = temp->next->next;
	ft_lstdelone(var_node, free);
}

void	ft_lstremove_2(t_list **lst, char *value)
{
	t_list	*var_node;
	t_list	*temp;

	temp = *lst;
	var_node = ft_lstfind_2(*lst, value);
	if (!var_node)
		return ;
	if (temp == var_node)
	{
		*lst = (*lst)->next;
		ft_lstdelone(var_node, free);
		return ;
	}
	while (temp->next != var_node)
		temp = temp->next;
	temp->next = temp->next->next;
	ft_lstdelone(var_node, free);
}

t_list	*ft_lstfind(t_list *lst, char *value)
{
	char	*temp;

	while (lst)
	{
		temp = ft_strjoin(value, "=");
		if (!ft_strncmp((char *)lst->content, temp, ft_strlen(temp)))
		{
			free(temp);
			return (lst);
		}
		free(temp);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*ft_lstfind_2(t_list *lst, char *value)
{
	while (lst)
	{
		if (!ft_strcmp((char *)lst->content, value))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
