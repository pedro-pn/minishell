/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:30:58 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/07 13:33:59 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile(t_data *data, t_cmd *exec, int process)
{
	int	fd;

	if (verify_infile(data, exec, process))
		return ;
	fd = open(exec->in_file, exec->mode_in);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->in_file);
		close(data->procs.pipes[process][0]);
		exit(1) ;
	}
	dup2(fd, 0);
	close(fd);
}

void	get_here_doc(t_cmd *exec)
{
	char	*line;
	char	*delimiter;

	line = NULL;
	pipe(exec->here_pipe);
	line = readline("> ");
	while (line)
	{
		if (!ft_strcmp(line, exec->delimiter))
			break ;
		write(exec->here_pipe[1], line, ft_strlen(line));
		write(exec->here_pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (!line)
		printf(EOF_DOC, exec->delimiter);
	close(exec->here_pipe[1]);
	free(line);
}

void	check_outfile(t_data *data, t_cmd *exec, int process)
{
	int	fd;

	if (verify_outfile(data, exec, process))
		return ;
	fd = open(exec->out_file, exec->mode_out, 0664);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->out_file);
		close(data->procs.pipes[process + 1][1]);
		exit (1);
	}
	dup2(fd, 1);
	close(fd);
}