/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:00:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 14:42:34 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	cmd->mode_in = 0;
	cmd->mode_out = 0;
	cmd->here_doc = 0;
	return (cmd);
}

void	init_processes(t_process *procs)
{
	procs->pids = NULL;
	procs->pipes = NULL;
}
