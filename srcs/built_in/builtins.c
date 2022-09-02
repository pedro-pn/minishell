/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:17:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/02 17:16:20 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_executor(t_data *data, char **cmds)
{
	if (!ft_strcmp(cmds[0], "cd"))
		__cd(cmds, data);
	if (!ft_strcmp(cmds[0], "export"))
		__export(cmds, data);
	if (!ft_strcmp(cmds[0], "unset"))
		__unset(cmds, data);
	if (!ft_strcmp(cmds[0], "exit"))
		exit(0);
	if (!ft_strcmp(cmds[0], "clear"))
		system("clear");
	return (0);
}

int	is_builtin(t_data *data, t_cmd *exec, int process)
{
	if (!*exec->cmd)
		return(0);
	if (!ft_strcmp(exec->cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "env"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "export"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(exec->cmd[0], "exit"))
		exit(0);
	if (!ft_strcmp(exec->cmd[0], "clear")
		&& process == data->procs.processes_n - 1)
		return (1);
	return (0);
}

void	builtin_executor_2(t_data *data, t_cmd *exec)
{
	char	*cmd;

	cmd = exec->cmd[0];
	if (!ft_strcmp(cmd, "echo"))
		__echo(exec->cmd, data);
	else if (!ft_strcmp(cmd, "cd"))
		__cd(exec->cmd, data); // g_status = __cd(args, data);
	else if (!ft_strcmp(cmd, "pwd"))
		__pwd(exec->cmd);
	else if (!ft_strcmp(cmd, "env"))
		__env(exec->cmd, data);
	else if (!ft_strcmp(cmd, "export"))
		__export(exec->cmd, data); // g_status = __export(args, data);
	else if (!ft_strcmp(cmd, "unset"))
		__unset(exec->cmd, data);
	else if (!ft_strcmp(cmd, "exit")) //esse comando é o unico que será executado fora do fork()
		exit(0); // porém ele só pode ser executado quando data->procs.processes_n == 1
	else if (!ft_strcmp(cmd, "clear"))
		system("clear"); // so por hora
}
