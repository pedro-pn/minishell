/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 18:58:22 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes prompt struct variables*/
void	prompt_init(t_prompt *prompt)
{
	prompt->line = NULL;
	prompt->directory = getcwd(NULL, 0);
}

/* Initializes struct s_cmds*/
t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->delimiter = NULL;
	cmd->mode = 0;
	cmd->here_doc = 0;
	return (cmd);
}