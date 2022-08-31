/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:30:58 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/31 16:33:28 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile(int *pipe, t_cmd *exec)
{
	int	fd;

	if (exec->here_doc)
	{
		dup2(exec->here_pipe[0], 0);
		close(exec->here_pipe[0]);
		return ;
	}
	if (!exec->in_file)
	{
		dup2(pipe[0], 0);
		close(pipe[0]);
		return ;
	}
	fd = open(exec->in_file, exec->mode_in);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->in_file);
		dup2(pipe[0], 0);
		close(pipe[0]);
		return ;
	}
	dup2(fd, 0);
	close(fd);
}

void	get_here_doc(t_cmd *exec)
{
	char	*buff;
	int		i;
	int		dlm_len;
	int		middle;
	char	*delimiter;

	delimiter = ft_strjoin(exec->delimiter, "\n");
	dlm_len = ft_strlen(delimiter);
	middle = 0;
	buff = ft_calloc(dlm_len + 1, sizeof(*buff));
	pipe(exec->here_pipe);
	while (ft_memset(buff, 0, dlm_len), read(STDIN_FILENO, buff, dlm_len)) // Pretendo alterar o here_doc para usar GNL
	{
		i = -1;
		if ((!ft_strncmp(buff, delimiter, dlm_len)) && middle == 0)
			break ;
		while (i++, buff[i])
			write(exec->here_pipe[1], &buff[i], 1);
		middle = 1;
		if (buff[i - 1] == '\n')
			middle = 0;
	}
	free(delimiter);
	close(exec->here_pipe[1]);
	free(buff);
}

void	check_outfile(t_data *data, t_cmd *exec, int process)
{
	int	fd;

	if (process == data->procs.processes_n - 1 && !exec->out_file)
	{
		close(data->procs.pipes[process + 1][1]);
		return ;
	}
	else if (!exec->out_file)
	{
		dup2(data->procs.pipes[process + 1][1], 1);
		close(data->procs.pipes[process + 1][1]);
		return ;
	}
	fd = open(exec->out_file, exec->mode_out, 0664);
	dup2(fd, 1);
	close(fd);
}