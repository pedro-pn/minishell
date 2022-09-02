/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:12:56 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 18:53:45 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_len(char **cmd_line);
static char	*format_cmd(char *cmd);

/* Gets the cmd line with its arguments and adds it to the t_cmd structure
as a char ** array*/
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
			remove_quotes(&((*exec_cmds)->cmd)[index]);
			index++;
		}
		index_cmd++;
	}
}

/* Counts the number of commands given by the user, excluding input/output files
*/
static int	get_cmd_len(char **cmd_line)
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

/* Formats the command properly to avoid input/output file markers*/ 
static char	*format_cmd(char *cmd)
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

// static void	remove_quotes(char **str)
// {
// 	char	*string;
	
// 	if ((*str)[0] == 34)
// 	{
// 		string = ft_strtrim(*str, "\"");
// 		free(*str);
// 		*str = string;
// 	}
// 	else if ((*str)[0] == 39)
// 	{
// 		string = ft_strtrim(*str, "\'");
// 		free(*str);
// 		*str = string;
// 	}
// }
