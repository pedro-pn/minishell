/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/25 15:35:55 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**env;
	char	**builtins;
	int		bk_stdin;
	int		bk_stdout;
	int		bk_stderr;
	int		old_status;
}		t_data;

typedef struct s_prompt
{
	char	*directory;
	char	*line;
}			t_prompt;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*in_file;
	char	*out_file;
	char	*delimiter;
	int		mode;
	int		here_doc;
}			t_cmd;

//int		g_exit_code;

// init
void	data_init(t_data *data, char **ep);

// prompt
void		show_prompt(t_prompt *prompt);
void		save_line(char *line);
void		prompt_init(t_prompt *prompt);
char		*update_message(char *dir);

// parser
t_list		*parser_input(char *line);
t_list	*create_input_list(char	*line);
t_cmd	*cmd_init(void);

// token
char		**get_input(char *line);

// signals
void		signals_setup(void);

// clean program
void	clean_array(void **array);
void	clean_cmd_lines(void *content);

// pipe_parser
void	validate_pipes(t_prompt *prompt);

// utils
void	free_split(char **matrix);

#endif