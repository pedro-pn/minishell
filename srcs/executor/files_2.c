/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:33:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/29 18:07:31 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_infile(t_data *data, t_cmd *exec, int process)
{
	if (exec->here_doc)
	{
		dup2(exec->here_pipe[0], 0);
		close(exec->here_pipe[0]);
		return (1);
	}
	if (!exec->in_file)
	{
		if (process != 0)
			dup2(data->procs.pipes[process][0], 0);
		close(data->procs.pipes[process][0]);
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

void	redirection_wildcard(char *file, int process)
{
	t_list	*infile_wc;

	infile_wc = NULL;
	infile_wc = ft_lstnew(ft_strdup(file));
	expand_wildcard(&infile_wc);
	if (ft_lstsize(infile_wc) != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		close(g_data.procs.pipes[process][0]);
		close(g_data.procs.pipes[process + 1][1]);
		ft_lstclear(&infile_wc, free);
		clean_executor();
		exit(1);
	}
	free(file);
	file = ft_strdup((char *)infile_wc->content);
	ft_lstclear(&infile_wc, free);
}
