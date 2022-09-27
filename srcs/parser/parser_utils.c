/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:16:49 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 12:34:21 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_flag(char c, int flag)
{
	if (c == '\"' && !(flag & QUOTE_S))
		flag ^= QUOTE_D;
	else if (c == '\'' && !(flag & QUOTE_D))
		flag ^= QUOTE_S;
	return (flag);
}

void	reset_infile(t_cmd *exec_cmds)
{
	free(exec_cmds->in_file);
	free(exec_cmds->delimiter);
	exec_cmds->in_file = NULL;
	exec_cmds->delimiter = NULL;
}

void	reset_outfile(t_cmd *exec_cmds)
{
	free(exec_cmds->out_file);
	exec_cmds->out_file = NULL;
}

/* Get input files in the user input, signalized by '<' or '<<'*/
void	get_infile(t_cmd *exec_cmds, char *cmd, int *st, int *ed)
{
	int	flag;

	flag = 0;
	reset_infile(exec_cmds);
	*ed = *st + 1;
	if (cmd[*ed] == '<')
	{
		exec_cmds->here_doc = 1;
		(*ed)++;
	}
	while (cmd[*ed] == ' ')
		(*ed)++;
	(exec_cmds)->mode_in = O_RDONLY;
	*st = *ed;
	while (!((cmd[*ed] == ' ' && !(flag & 3)) || !cmd[*ed]))
	{
		flag = quote_flag(cmd[(*ed)], flag);
		(*ed)++;
	}
	if (exec_cmds->here_doc == 1)
		exec_cmds->delimiter = trim_spc(ft_substr(cmd, *st, *ed - *st));
	else
		exec_cmds->in_file = trim_spc(ft_substr(cmd, *st, *ed - *st));
	*st = *ed + 1;
}

/* Get output files in the user input, signalized by '>' or '>>'*/
void	get_outfile(t_cmd *exec_cmds, char *cmd, int *st, int *ed)
{
	int	flag;

	flag = 0;
	reset_outfile(exec_cmds);
	*ed = *st + 1;
	if (cmd[*ed] == '>')
	{	
		exec_cmds->mode_out = O_APPEND | O_CREAT | O_WRONLY;
		(*ed)++;
	}
	else
		exec_cmds->mode_out = O_CREAT | O_WRONLY | O_TRUNC;
	while (cmd[*ed] == ' ')
		(*ed)++;
	*st = *ed;
	while (!((cmd[*ed] == ' ' && !(flag & 3)) || !cmd[*ed]))
	{
		flag = quote_flag(cmd[*ed], flag);
		(*ed)++;
	}
	exec_cmds->out_file = trim_spc(ft_substr(cmd, *st, *ed - *st));
	*st = *ed + 1;
}
