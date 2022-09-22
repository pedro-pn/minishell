/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:31:10 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/22 11:32:06 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_variable(t_data *data, char *arg, char *var)
{
	t_list	*var_node;

	var_node = ft_lstfind(data->lst_env, var);
	if (var_node)
	{
		free(var_node->content);
		var_node->content = ft_strdup(arg);
		return ;
	}
	ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strdup(arg)));
}

void	append_variable(t_data *data, char *arg, char *var)
{
	t_list	*var_node;
	char	*temp;

	*ft_strchr(var, '+') = 0;
	var_node = ft_lstfind(data->lst_env, var);
	if (var_node)
	{
		temp = (char *) var_node->content;
		var_node->content = ft_strjoin(temp, ft_strchr(arg, '+') + 2);
		free(temp);
		return ;
	}
	temp = ft_strjoin(var, "=");
	ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strjoin(temp,
				ft_strchr(arg, '=') + 1)));
	free(temp);
}

int	check_for_append(char *var)
{
	char	*key;

	key = ft_strchr(var, '+');
	if (!key)
		return (0);
	if (*(++key) == 0)
		return (1);
	return (0);
}
