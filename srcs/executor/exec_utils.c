/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:55:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 11:55:00 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_pids(t_data *data)
{
	int	*pids;

	pids = ft_calloc(data->procs.processes_n, sizeof(*pids));
	return (pids);
}

void	output_exec_error(t_cmd *exec)
{
	if (ft_strchr(exec->cmd[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->cmd[0]);
	}
	else
	{
		ft_putstr_fd(exec->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
}