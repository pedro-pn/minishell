/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/30 14:36:30 by ppaulo-d         ###   ########.fr       */
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

# define META_C "><"
# define PATH_MAX 4096

# define ERR_PIPE "-minishell: syntax error near unexpected token `|'"
# define ERR_NEWL "-minishell: syntax error near unexpected token `newline'"

//int		g_status;

typedef struct s_prompt
{
	char	*directory;
	char	*message;
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

typedef struct s_process
{
	int	**pipes;
	int	*pids;
	int	processes_n;
}			t_process;

typedef struct s_data
{
	t_list		*lst_env;
	t_list		*exec_data;
	t_list		*empty_vars;
	char		**arr_env;
	char		**builtins;
	int			cmd_count;
	int			is_pipe_empty;
	t_prompt	prompt;
	t_process	procs;
}			t_data;


// init
void	init_prompt(t_prompt *prompt);
void	init_data(t_data *data, char **ep);

// prompt
void		show_prompt(t_data *data);
void		save_history(char *line);
char		*update_prompt_msg(t_data *data);

// parser
t_list		*parser_input(char *line);
t_list	*create_input_list(char	*line);
t_cmd	*cmd_init(void);
void	get_cmd(char **cmd_line, t_cmd **exec_cmds);

// token
char		**get_input(char *line);

// signals
void		signals_setup(void);

// clean program
void	clean_array(void **array);
void	clean_cmd_lines(void *content);
void	clean_s_cmd(void *content);
void	clean_prompt(t_prompt *prompt);

// validate pipes
void	validate_pipes(t_data *data);

// validate redirections
void	validate_redirections(t_data *data);

// utils
void	ft_arrdisplay(char **a);
void	ft_lstdisplay(t_list *lst);
void	raise_error(char *msg, int errn);
char	**get_array_from_lst(t_list *lst);
t_list	*get_lst_from_array(char **arr);
void	ft_lstremove(t_list **lst, char *value);
t_list	*ft_lstfind(t_list *lst, char *value);
char	*ft_lstfind_value(t_list *lst, char *value);
void	ft_lstremove_2(t_list **lst, char *value);

char	*get_key(char *str);
char	*get_value(char *str);
void	*get_declared_vars(void *content);
t_list	*ft_lstfind_2(t_list *lst, char *value);

// Built-ins
void	__echo(char **args);
void	__cd(char **args, t_data *data);
void	__pwd(char **args);
void	__env(char **args, t_data *data);
void	__export(char **args, t_data *data);
void	__unset(char **args, t_data *data);

// Debbug - delete later
void	print_content(char **array);

#endif