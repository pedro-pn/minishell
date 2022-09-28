/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:21:15 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 05:32:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/* executor.c functions */

int		executor(t_data *data);

/* exec_utils.c functions */

void	exec_init(t_data *data);
int		*get_pids(t_data *data);
void	output_exec_error(t_cmd *exec);

/* exec_wait.c functions */

int		wait_executor(t_data *data);
int		wait_processes(t_data *data, int processes_n);

/* files.c functions */

void	check_infile(t_data *data, t_cmd *exec, int process);
void	get_here_doc(t_cmd *exec);
void	check_outfile(t_data *data, t_cmd *exec, int process);

/* files_2.c functions */

int		verify_infile(t_data *data, t_cmd *exec, int process);
int		verify_outfile(t_data *data, t_cmd *exec, int process);

/* path.c functions */

void	get_path(t_data *data, char **cmd, char **path);

/* pipes.c functions */

int		**get_pipes(t_data *data);
int		open_pipes(t_data *data);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes);

#endif
