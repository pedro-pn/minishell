/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:55:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/12 12:41:11 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(char *cmd, t_data *data);
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
	g_status = 127;
}

void	expand(char *cmd, t_data *data)
{
	t_list	*node;
	char	*var;
	char	*key;
	char	*value;

	// printf("%s\n", cmd);
	// exit(1);
	if (*cmd == '\'')
		return ;
	var = ft_strtrim(cmd, "\"");
	if (ft_strchr(cmd, '$'))
		key = ft_strchr(var, '$') + 1;
	else
		key = cmd;
	node = ft_lstfind(data->lst_env, key);
	if (!ft_strcmp(key, "?"))
		value = ft_itoa(g_status);
	else if (!node)
		value = ft_strdup("");
	else
		value = get_value((char *)node->content);
	free(cmd);
	cmd = ft_strdup(value);
	free(value);
	free(var);
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
			expand(exec->cmd[i], data);
		if (*exec->cmd[i])
			buff = parse_cmd(buff, exec->cmd[i]);
	}
	clean_array((void **)exec->cmd);
	verify_quotes(buff);
	clean_quotes(buff, 39, 32, CTRL_SPC);
	clean_quotes(buff, 34, 32, CTRL_SPC);
	exec->cmd = ft_split(buff, ' ');
	restore_quotes(exec->cmd);
	free(buff);
}

static int	check_first_cmd(char *str)
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
