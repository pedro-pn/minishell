/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:20:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 12:31:48 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	int		last_status_code;
	t_cmd	*exec;

	exec = (t_cmd *)data->exec_data->content;
	if (ft_lstsize(data->exec_data) == 1 && exec->cmd)
		builtin_executor(data, exec->cmd);
	data->procs.exec_pid = fork();
	executor_signals(data->procs.exec_pid, 0);
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
	rl_clear_history();
	exit(last_status_code);
}

void	_exec(t_data *data, t_list *exec_data)
{
	int		process;
	t_cmd	*exec;

	process = 0;
	while (process < data->procs.processes_n)
	{
		exec = (t_cmd *)exec_data->content;
		get_path(data, exec->cmd, &exec->path);
		if (exec->here_doc)
		{	
			heredoc_signals(data->procs.pids[process], 1);
			if (data->procs.pids[process] == 0)
				get_here_doc(exec);
		}
		data->procs.pids[process] = fork();
		executor_signals(data->procs.pids[process], 1);
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
	if (is_builtin(data, exec, process))
		builtin_executor_2(data, exec);
	else if (exec->path)
		execve(exec->path, exec->cmd, env);
	else if (exec->cmd)
		output_exec_error(exec);
	ft_lstclear(&(data->exec_data), clean_s_cmd);
	ft_lstclear(&data->lst_env, free);
	clean_processes(&data->procs);
	clean_data(data);
	clean_array((void **)env);
	rl_clear_history();
	exit(data->status);
}
