/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:19:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/04 10:17:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_spc(char *str)
{
	char	*temp;

	temp = str;
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}

void	clean_empty_nodes(t_list **lst)
{
	t_list	*temp;
	int		empty_nodes;

	temp = *lst;
	empty_nodes = 0;
	while (temp)
	{
		if (!ft_strcmp((char *)temp->content, ""))
			empty_nodes++;
		temp = temp->next;
	}
	while (empty_nodes > 0)
	{
		ft_lstremove_2(lst, "");
		empty_nodes--;
	}
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

void	throw_pipe_error(int err, t_data *data)
{
	if (err == 1)
		ft_putendl_fd(ERR_PIPE1, 2);
	else if (err == 2)
		ft_putendl_fd(ERR_PIPE2, 2);
	data->invalid_syntax = 1;
	data->status = 2;
}
