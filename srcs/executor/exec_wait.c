/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:14:45 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/04 10:20:16 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_executor(t_data *data)
{
	int	status;
	int	status_code;

	status_code = 0;
	status = 0;
	waitpid(data->procs.exec_pid, &status, 0);
	if (WIFSIGNALED(status))
		status_code = handle_signals(data, status, 0, 1);
	else if (WIFEXITED(status))
		status_code = WEXITSTATUS(status);
	return (status_code);
}

int	wait_processes(t_data *data, int processes_n)
{
	int	process;
	int	status;
	int	status_code;

	process = 0;
	while (process < processes_n)
	{
		waitpid(data->procs.pids[process], &status, 0);
		if (WIFSIGNALED(status))
			status_code = handle_signals(data, status, process, processes_n);
		else if (WIFEXITED(status))
			if (process == processes_n - 1)
				status_code = WEXITSTATUS(status);
		process++;
	}
	return (status_code);
}
