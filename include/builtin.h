/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:41:02 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/30 17:24:09 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define PATH_MAX 4096

/* builtins.c file */

int		builtin_executor(t_data *data, char **cmds);
int		is_builtin(t_data *data, t_cmd *exec, int process);
void	builtin_executor_2(t_data *data, t_cmd *exec);

/* cd.c file */

int		__cd(char **args, t_data *data);

/* echo.c file */

int		__echo(char **args);

/* env.c file */

int		__env(t_data *data);

/* export.c files */

int		__export(char **args, t_data *data);

/* export_utils.c files */

void	update_variable(t_data *data, char *arg, char *var);
void	append_variable(t_data *data, char *arg, char *var);
int		check_for_append(char *var);

/* pwd.c functions */

int		__pwd(void);

/* unset.c functions */

int		__unset(char **args, t_data *data);

#endif
