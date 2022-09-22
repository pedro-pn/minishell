/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:44:03 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/22 11:19:11 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_pipes(t_data *data)
{
	int	index;
	int	**pipes;

	index = 0;
	pipes = malloc(sizeof(*pipes) * (data->procs.processes_n + 2));
	pipes[data->procs.processes_n + 1] = NULL;
	while (index < data->procs.processes_n + 1)
	{
		pipes[index] = malloc(2 * sizeof(**pipes));
		index++;
	}
	return (pipes);
}

int	open_pipes(t_data *data)
{
	int	index;

	index = 0;
	while (data->procs.pipes[index])
	{
		pipe(data->procs.pipes[index]);
		index++;
	}
	return (0);
}

void	close_child_pipes(int **pipes, int process)
{
	int	index;

	index = 0;
	while (pipes[index])
	{
		if (index != process)
			close(pipes[index][0]);
		if (index != process + 1)
			close(pipes[index][1]);
		index++;
	}
}

void	close_main_pipes(int **pipes)
{
	int	index;

	index = 0;
	while (pipes[index])
	{
		close(pipes[index][0]);
		close(pipes[index][1]);
		index++;
	}
}
