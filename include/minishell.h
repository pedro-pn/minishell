/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/23 21:58:51 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef struct s_prompt
{
	char	*directory;
	char	*line;
}			t_prompt;

int		g_exit_code;

// prompt
void	show_prompt(t_prompt *prompt);
void	save_line(char *line);
void	prompt_init(t_prompt *prompt);
char	*update_message(char *dir);

// parser
int		parser_input(char *line);

// token
char	**get_input(char *line);

// signals
void	signals_setup(void);

#endif