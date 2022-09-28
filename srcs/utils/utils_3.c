/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:08:37 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/22 11:10:19 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
