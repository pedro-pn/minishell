/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:44:03 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:36 by ppaulo-d         ###   ########.fr       */
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
		pipe(data->procs.pipes[index]) == -1;
		index++;
	}
	return (0);
}