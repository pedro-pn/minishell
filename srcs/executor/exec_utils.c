/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d < ppaulo-d@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:55:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/08 21:57:08 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(char **cmd, t_data *data);
static int	check_first_cmd(char *str);

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

void	expand(char **cmd, t_data *data)
{
	t_list	*node;
	char	*key;
	char	*value;
	char	*to_find;

	int i = 0;
	while (*cmd[i] != '$')
		i++;
	key = ft_substr(*cmd, 0, i);
	to_find = ft_strchr(*cmd, '$') + 1;
	node = ft_lstfind(data->lst_env, to_find);
	if (!ft_strcmp(to_find, "?"))
		value = ft_itoa(g_status);
	else if (!node)
		value = ft_strdup("");
	else
		value = get_value((char *)node->content);
	free(*cmd);
	*cmd = ft_strjoin(key, value);
	free(key);
	free(value);
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

void	expand_variables(t_data *data, t_cmd *exec)
{
	char	*buff;
	int		i;

	if (!exec->cmd)
		return ;
	if (check_first_cmd(exec->cmd[0]) || !ft_strcmp(exec->cmd[0], "awk"))
		return ;
	i = -1;
	buff = ft_strdup("");
	while (exec->cmd[++i])
	{
		if (ft_strchr(exec->cmd[i], '$'))
			expand(&exec->cmd[i], data);
		if (*exec->cmd[i])
			buff = parse_cmd(buff, exec->cmd[i]);
	}
	clean_array((void **)exec->cmd);
	exec->cmd = ft_split(buff, ' ');
	free(buff);
}

static int	check_first_cmd(char *str)
{
	char	*cmd;

	if (!str)
		return (1);
	cmd = ft_strtrim(str, " ");
	if (ft_strlen(cmd) == 1 && *cmd == '$')
		return (1);
	return (0);
}
