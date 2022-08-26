/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:12:56 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/25 23:37:35 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_len(char **cmd_line);
char	*format_cmd(char *cmd);

void	get_cmd(char **cmd_line, t_cmd **exec_cmds)
{
	int	index;
	int	index_cmd;
	int	cmd_len;

	index = 0;
	index_cmd = 0;
	cmd_len = get_cmd_len(cmd_line);
	(*exec_cmds)->cmd = malloc(sizeof(*(*exec_cmds)->cmd) * (cmd_len + 1));
	((*exec_cmds)->cmd)[cmd_len] = NULL;
	while (index < cmd_len)
	{
		if (!ft_strchr(META_C, cmd_line[index_cmd][0]))
		{
			((*exec_cmds)->cmd)[index] = format_cmd(cmd_line[index_cmd]);
			index++;
		}
		index_cmd++;
	}
}

int	get_cmd_len(char **cmd_line)
{
	int counter;
	int	index;
	int	inout_file;

	counter = 0;
	index = 0;
	while (cmd_line[index])
	{
		if (!ft_strchr(META_C, cmd_line[index][0]))
			counter++;
		index++;
	}
	return (counter);
}

char	*format_cmd(char *cmd)
{
	int	index;
	int	quote_s;
	int	quote_d;

	index = 0;
	quote_s = 1;
	quote_d = 1;
	while (cmd[index])
	{
		if (cmd[index] == 39 && quote_d == 1)
			quote_s *= -1;
		if (cmd[index] == 34 && quote_s == 1)
			quote_d *= -1;
		if (ft_strchr(META_C, cmd[index]) && quote_s == 1 && quote_d == 1)
			break ;
		index++;
	}
	return (ft_substr(cmd, 0, index));
}
