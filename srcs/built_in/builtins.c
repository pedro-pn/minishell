/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:17:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/01 07:43:53 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "clear"))
		return (1);
	return (0);
}

void	builtin_executor(char **args, t_data *data)
{
	char	*cmd;

	cmd = args[0];
	if (!ft_strcmp(cmd, "echo"))
		__echo(args);
	else if (!ft_strcmp(cmd, "cd"))
		__cd(args, data); // g_status = __cd(args, data);
	else if (!ft_strcmp(cmd, "pwd"))
		__pwd(args);
	else if (!ft_strcmp(cmd, "env"))
		__env(args, data);
	else if (!ft_strcmp(cmd, "export"))
		__export(args, data); // g_status = __export(args, data);
	else if (!ft_strcmp(cmd, "unset"))
		__unset(args, data);
	else if (!ft_strcmp(cmd, "exit"))
		exit(0); // clean before exit
	else if (!ft_strcmp(cmd, "clear"))
		system("clear"); // so por hora
}
