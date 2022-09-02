/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:33:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 10:54:47 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_infile(int *pipe, t_cmd *exec)
{
	if (exec->here_doc)
	{
		dup2(exec->here_pipe[0], 0);
		close(exec->here_pipe[0]);
		return (1);
	}
	if (!exec->in_file)
	{
		dup2(pipe[0], 0);
		close(pipe[0]);
		return (1);
	}
	return (0);
}

int	verify_outfile(t_data *data, t_cmd *exec, int process)
{
	if (process == data->procs.processes_n - 1 && !exec->out_file)
	{
		close(data->procs.pipes[process + 1][1]);
		return (1);
	}
	else if (!exec->out_file)
	{
		dup2(data->procs.pipes[process + 1][1], 1);
		close(data->procs.pipes[process + 1][1]);
		return (1);
	}
	return (0);
}