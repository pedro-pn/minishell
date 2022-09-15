/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:55:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/15 11:10:41 by frosa-ma         ###   ########.fr       */
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
	struct stat path_stat;
	
	stat(exec->cmd[0], &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putendl_fd(" Is a directory", 2);
		g_status = 126;
	}
	else if (ft_strchr(exec->cmd[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->cmd[0]);
		g_status = 127;
	}
	else
	{
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		g_status = 127;
	}
}

char	*parse_cmd(char *buff, char *arg)
{
	char	*pb;

	pb = buff;
	buff = ft_strjoin(pb, arg);
	free(pb);
	pb = buff;
	buff = ft_strjoin(pb, " ");
	free(pb);
	return (buff);
}

int	check_first_cmd(char *str)
{
	char	*cmd;

	if (!str)
		return (1);
	cmd = ft_strtrim(str, " ");
	if (ft_strlen(cmd) == 1 && *cmd == '$')
	{
		free(cmd);
		return (1);
	}
	free(cmd);	
	return (0);
}

char	*_get_value(char *key, t_list *node)
{
	char	*value;

	value = NULL;
	if (*key == '?')
		value = ft_itoa(g_status);
	else if (!node)
		value = ft_strdup("");
	else
		value = get_value((char *)node->content);
	return (value);
}
