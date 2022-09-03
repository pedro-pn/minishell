/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:20:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/03 11:44:36 by ppaulo-d         ###   ########.fr       */
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

void	_exec(t_data *data, t_list *exec_data)
{
	int		process;
	t_cmd	*exec;

	process = 0;
	while (process < data->procs.processes_n)
	{
		exec = (t_cmd *)exec_data->content;
		get_path(data, &exec->cmd[0], &exec->path);
			//ft_printf("%s: command not found\n", exec->cmd[0]);
		if (exec->here_doc)
			get_here_doc(exec);
		if (data->procs.processes_n == 1 && *exec->cmd)
			builtin_executor(data, exec->cmd);
		data->procs.pids[process] = fork();
		if (data->procs.pids[process] == 0)
			exec_child(data, exec, process);
		if (exec->here_doc)
			close((exec->here_pipe)[0]);
		process++;
		exec_data = exec_data->next;
	}
}

void	exec_child(t_data *data, t_cmd *exec, int process)
{
	char	**env;
	int		i;

	env = get_array_from_lst(data->lst_env);
	//ft_printf("path: %s\ncmd: %s\n", exec->path, exec->cmd[1]);
	close_child_pipes(data->procs.pipes, process);
	check_infile(data->procs.pipes[process], exec);
	check_outfile(data, exec, process);
	i = 0;
	while (exec->cmd[++i])
		if (exec->cmd[i][0] == '$')
			expand(exec->cmd[i], data);
	if (is_builtin(data, exec, process))
		builtin_executor_2(data, exec);
	else if (exec->path)
		execve(exec->path, exec->cmd, env);
	else if (*exec->cmd)
		output_exec_error(exec);
	clean_data(data);
	// se chegar aqui, limpar tudo, significa que o comando n existe
	//talvez seja necessario fechar os pipes
	exit(EXIT_FAILURE);
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
		if (WIFEXITED(status))
		{
			if (process == processes_n - 1)
				status_code = WEXITSTATUS(status);
		}
		process++;
	}
	return (status_code);
}
