/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:23:45 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/19 20:25:55 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrdisplay(char **a)
{
	while (*a)
		printf("%s\n", *a++);
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

char	*ft_chtos(char ch)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	*str = ch;
	return (str);
}

char	*get_str_from_lst(t_list *lst)
{
	char	*str;
	char	*p;

	str = (char *)malloc((ft_lstsize(lst) + 1) * sizeof(char));
	p = str;
	while (lst)
	{
		*p++ = *(char *)lst->content;
		lst = lst->next;
	}
	return (str);
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
