/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:20:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/07 13:18:28 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	int	last_status_code;
	
	exec_init(data);
	_exec(data, data->exec_data);
	close_main_pipes(data->procs.pipes);
	last_status_code = wait_processes(data, data->procs.processes_n);
	main_signals();
	clean_processes(&data->procs);
	ft_lstclear(&(data->exec_data), clean_s_cmd);

	// temos que achar uma forma depois de armazenar esse retorno lá no prompt
	// para uma variavel. Será necessaário para o comando $?
	return (last_status_code);
}

void	exec_init(t_data *data)
{
	data->procs.processes_n = ft_lstsize(data->exec_data);
	data->procs.pids = get_pids(data);
	data->procs.pipes = get_pipes(data);
	open_pipes(data);
}

// static char	*parse_input(t_data *data)
// {
// 	char	**token;
// 	char	*str;
// 	char	*p;
// 	char	*q;
// 	int		i;

// 	str = ft_strdup("");
// 	token = (char **)ft_split(data->prompt.line, '|');
// 	i = -1;
// 	while (++i < data->cmd_count)
// 	{
// 		p = ft_strjoin(token[i], "|");
// 		q = str;
// 		str = ft_strjoin(q, p);
// 		free(q);
// 		free(p);
// 	}
// 	p = str;
// 	str = ft_strtrim(p, "|");
// 	free(p);
// 	return (str);
// }

void	_exec(t_data *data, t_list *exec_data)
{
	int		process;
	t_cmd	*exec;

	process = 0;
	// if (data->is_pipe_empty)
	// {
	// 	data->prompt.line = (char *)parse_input(data);
	// 	data->exec_data = parser_input(data->prompt.line);
	// }
	while (process < data->procs.processes_n)
	{
		exec = (t_cmd *)exec_data->content;
		get_path(data, &exec->cmd[0], &exec->path);
		if (data->procs.processes_n == 1 && *exec->cmd)
			builtin_executor(data, exec->cmd);
		data->procs.pids[process] = fork();
		executor_signals(data->procs.pids[process]);
		if (exec->here_doc)
		{	
			heredoc_signals(data->procs.pids[process]);
			if (data->procs.pids[process] == 0)
				get_here_doc(exec);
		}
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
	// if (!data->is_pipe_empty)
	// {
	// 	close_child_pipes(data->procs.pipes, process);
	// 	check_infile(data, exec, process);
	// 	check_outfile(data, exec, process);
	// }

	close_child_pipes(data->procs.pipes, process);
	check_infile(data, exec, process);
	check_outfile(data, exec, process);

	expand_variables(data, exec);

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
