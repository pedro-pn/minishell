/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:25:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/29 12:11:17 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exibe o array de strings
void	ft_arrdisplay(char **a)
{
	while (*a)
		printf("%s\n", *a++);
}

// Exibe a lista
void	ft_lstdisplay(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		ft_lstdisplay(lst->next);
	printf("%s\n", (char *)lst->content);
}

void	raise_error(char *msg, int errn)
{
	ft_putendl_fd(msg, 2);
	// g_status = errn;
}

// Gera uma array de strings a partir de uma lista
char	**get_array_from_lst(t_list *lst)
{
	char	**arr;
	int		i;

	if (!lst)
		return (NULL);
	i = ft_lstsize(lst);
	arr = (char **)ft_calloc(i + 1, sizeof(*arr));
	if (!arr)
		return (NULL);
	while (lst)
	{
		arr[--i] = ft_strdup((char *)lst->content);
		lst = lst->next;
	}
	return (arr);
}

// Remove e retorna um node da lista com base no seu valor
//   lstsize(lst) -> 10 
//   lstremove(lst, "PATH")  ->  node("PATH")
//   lstsize(lst) -> 9 
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

// retorna um pointer para o elemento da lista com base no seu valor
//    lstfind(lst, "SHLVL")  ->  node("SHLVL=1")
//    lstfind(lst, "PATH")  ->  node("PATH=/bin/:/usr/bin:...")
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

// retorna uma string a partir do conteudo de um node
//    "SHLVL=1"  ->  "1"
//    "PATH=/bin/:/usr/bin/..."  ->  "/bin/:/usr/bin/..."
char	*ft_lstfind_value(t_list *lst, char *value)
{
	t_list	*node;
	char	*str;

	if (!ft_lstfind(lst, value))
		return (NULL);
	node = ft_lstfind(lst, value);
	str = ft_strchr((char *)node->content, '=') + 1;
	return (str);
}

// Gera uma lista a partir de um array de strings
t_list	*get_lst_from_array(char **arr)
{
	t_list	*lst;

	if (!arr)
		return (NULL);
	lst = NULL;
	while (*arr)
		ft_lstadd_front(&lst, ft_lstnew(ft_strdup(*arr++)));
	return (lst);
}
