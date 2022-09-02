/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:30:58 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 10:55:39 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile(int *pipe, t_cmd *exec)
{
	int	fd;

	if (verify_infile(pipe, exec))
		return ;
	fd = open(exec->in_file, exec->mode_in);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->in_file);
		close(pipe[0]);
	//	g_status = 1;
		exit(1) ;
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