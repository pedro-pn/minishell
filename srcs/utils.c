/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:25:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/29 21:14:52 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_var_quotes(char *str);

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

void	*get_declared_vars(void *content)
{
	char	*var;
	char	*empty_content;
	char	*quoted_var;

	if (!*(ft_strchr(((char *)content), '=') + 1))
	{
		empty_content = ft_strjoin((char *)content, "\"\"");
		var = ft_strjoin("declare -x ", empty_content);
		free(empty_content);
	}
	else
	{
		quoted_var = insert_var_quotes((char *)content);
		var = ft_strjoin("declare -x ", quoted_var);
		free(quoted_var);
	}
	return (var);
}

char	*insert_var_quotes(char *str)
{
	char	**key;
	char	*value;
	char	*temp;
	char	*final_str;
	char	*final_value;

	key = ft_split(str, '=');
	value = ft_strdup(ft_strchr(str, '=') + 1);
	temp = ft_strjoin("=\"", value);
	final_value = ft_strjoin(temp, "\"");
	final_str = ft_strjoin(key[0], final_value);
	free(temp);
	free(final_value);
	free(value);
	clean_array((void **)key);
	return (final_str);
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