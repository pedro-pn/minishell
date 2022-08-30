/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:20:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/30 17:40:18 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	exec_init(data);
}

void	exec_init(t_data *data)
{
	data->procs.processes_n = ft_lstsize(data->exec_data);
	data->procs.pids = NULL;
	data->procs.pipes = NULL;
	data->procs.pids = get_pids(data);
	data->procs.pipes = get_pipes(data);
	open_pipes(data);
}

int	*get_pids(t_data *data)
{
	int	*pids;

	pids = ft_calloc(data->procs.processes_n, sizeof(*pids));
	return (pids);
}

void	_exec(t_data *data, t_cmd *exec_data)
{
	int	process;

	process = 0;
	while (process < data->procs.processes_n)
	{
		if (get_path(data, &exec_data->cmd[0], &exec_data->path))
			ft_printf("minishell: %s: command not found\n", exec_data->cmd[0]);
		data->procs.pids[process] = fork();
		//if (data->pids[process] == -1)
		//	error handling
		//else if (data->procs.pids[process] == 0)
			//execute children process;
		
		process++;
	}
}

int	get_path(t_data *data, char **cmd, char **path)
{
	char	**bin_paths;
	t_list	*path_node;
	int		status;
	
	if (ft_strchr(*cmd, '/'))
		status = get_given_path(data, cmd, path);
	if (!status)
		return (status);
	path_node = ft_lstfind(data->lst_env, "PATH");
	bin_paths = ft_split((char *)path_node->content, ':');
	status = check_path(bin_paths, *cmd, path);
	clean_array((void **)bin_paths);
	return (status);
}

int	get_given_path(t_data *data, char **cmd, char **path)
{
	char	*name;

	if (access(*cmd, F_OK))
		return (1);
	name = ft_strdup(ft_strrchr(*cmd, '/') + 1);
	*path = *cmd;
	*cmd = name;
	return (0);
}	

int	check_path(char **bin_paths, char *cmd, char **path)
{
	int		index;
	char	*path_test;
	char	*temp;
	int		status;

	index = -1;
	while (index++, bin_paths[index])
	{
		temp = ft_strjoin(bin_paths[index], "/");
		path_test = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_test, F_OK) == 0)
		{
			status = 0;
			break ;
		}
		else
			status = 1;
		free(path_test);
		path_test = NULL;
	}
	*path = path_test;
	return (status);
}
