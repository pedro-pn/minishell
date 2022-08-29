/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:25:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/29 04:04:24 by frosa-ma         ###   ########.fr       */
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
	printf("%s\n", (char *)lst->content);
	if (lst->next)
		ft_lstdisplay(lst->next);
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
t_list	*ft_lstremove(t_list **lst, char *value)
{
	t_list	*elem;
	t_list	*curr;

	if (!ft_lstfind(*lst, value))
		return (NULL);
	elem = NULL;
	curr = *lst;
	if (curr && !ft_strncmp((char *)curr->content, value, ft_strlen(value)))
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		return (elem);
	}
	while (curr && curr->next)
	{
		if (!ft_strncmp((char *)curr->next->content, value, ft_strlen(value)))
		{
			elem = curr->next;
			curr->next = curr->next->next;
			elem->next = NULL;
			return (elem);
		}
		curr = curr->next;
	}
	return (NULL);
}

// retorna um pointer para o elemento da lista com base no seu valor
//    lstfind(lst, "SHLVL")  ->  node("SHLVL=1")
//    lstfind(lst, "PATH")  ->  node("PATH=/bin/:/usr/bin:...")
t_list	*ft_lstfind(t_list *lst, char *value)
{
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, value, ft_strlen(value)))
			return (lst);
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
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(*arr++)));
	return (lst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup(str + i + 1));
}
