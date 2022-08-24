/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 18:06:42 by ppaulo-d         ###   ########.fr       */
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

#endif