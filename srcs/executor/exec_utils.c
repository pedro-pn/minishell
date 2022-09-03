/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:55:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/03 11:42:07 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_pids(t_data *data)
{
	int	*pids;

	pids = ft_calloc(data->procs.processes_n, sizeof(*pids));
	return (pids);
}

void	output_exec_error(t_cmd *exec)
{
	if (ft_strchr(exec->cmd[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->cmd[0]);
	}
	else
	{
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	expand(char *cmd, t_data *data)
{
	t_list	*node;
	char	*key;
	char	*value;
	char	*to_find;

	int i = 0;
	while (cmd[i] != '$')
		i++;
	key = ft_substr(cmd, 0, i);
	to_find = ft_strchr(cmd, '$') + 1;
	node = ft_lstfind(data->lst_env, to_find);
	value = get_value((char *)node->content);
	free(cmd);
	cmd = ft_strjoin(key, value);
	free(key);
	free(value);
}
