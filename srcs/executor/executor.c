/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:20:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/09 11:55:10 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	int	last_status_code;
	
	if (ft_lstsize(data->exec_data) == 1
			&& ((t_cmd *)data->exec_data->content)->cmd)
		builtin_executor(data, ((t_cmd *)data->exec_data->content)->cmd);
	data->procs.exec_pid = fork();
	if (data->procs.exec_pid == 0)
		main_exec(data);
	last_status_code = wait_executor(data);
	main_signals();
	ft_lstclear(&(data->exec_data), clean_s_cmd);
	return (last_status_code);
}

int	main_exec(t_data *data)
{
	int	last_status_code;

	exec_init(data);
	_exec(data, data->exec_data);
	close_main_pipes(data->procs.pipes);
	last_status_code = wait_processes(data, data->procs.processes_n);
	clean_processes(&data->procs);
	ft_lstclear(&(data->exec_data), clean_s_cmd);
	clean_data(data);
	ft_lstclear(&data->lst_env, free);
	exit(last_status_code);
}

void	exec_init(t_data *data)
{
	data->procs.processes_n = ft_lstsize(data->exec_data);
	data->procs.pids = get_pids(data);
	data->procs.pipes = get_pipes(data);
	open_pipes(data);
}

void	_exec(t_data *data, t_list *exec_data)
{
	int		process;
	t_cmd	*exec;

	process = 0;
	while (process < data->procs.processes_n)
	{
		exec = (t_cmd *)exec_data->content;
		get_path(data, &exec->cmd[0], &exec->path);
		if (exec->here_doc)
		{	
			heredoc_signals(data->procs.pids[process]);
			if (data->procs.pids[process] == 0)
				get_here_doc(exec);
		}
		expand_variables(data, exec);
		data->procs.pids[process] = fork();
		executor_signals(data->procs.pids[process]);
		if (data->procs.pids[process] == 0)
			exec_child(data, exec, process);
		process++;
		exec_data = exec_data->next;
	}
}

void	exec_child(t_data *data, t_cmd *exec, int process)
{
	char	**env;

	env = get_array_from_lst(data->lst_env);
	close_child_pipes(data->procs.pipes, process);
	check_infile(data, exec, process);
	check_outfile(data, exec, process);
	// expand_variables(data, exec);
	if (is_builtin(data, exec, process))
		builtin_executor_2(data, exec);
	else if (exec->path)
		execve(exec->path, exec->cmd, env);
	else if (*exec->cmd)
		output_exec_error(exec);
	clean_data(data);
	clean_array((void **)env);
	if (is_builtin(data, exec, process))
		exit(g_status);
	exit(127);
}

int	handle_signals(t_data *data, int status, int process, int processes_n)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
	}
	if (WTERMSIG(status) == SIGQUIT && process == processes_n - 1)
	{
		write(1, "Quit\n", 5);
		g_status = 131;
	}
	return (g_status);
}

int		wait_executor(t_data *data)
{
	int	status;
	int	status_code;

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
