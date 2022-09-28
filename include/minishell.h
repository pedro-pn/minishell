/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 12:14:47 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# define META_C ">< "
# define VAR_DELIMITER "$\"\'}{|><= "
# define QUOTES "\"\'"
# define QUOTE_S 1
# define QUOTE_D 2
# define OPEN_BCKT 4
# define PATH_MAX 4096

# define ERR_PIPE1 "-minishell: syntax error near unexpected token `|'"
# define ERR_PIPE2 "-minishell: syntax error near unexpected token `||'"
# define ERR_NEWL "-minishell: syntax error near unexpected token `newline'"
# define EOF_DOC "minishell: warning: heredoc delimited by EOF. Wanted "

# define RED "\001\x1b[38;5;88m\002"
# define BLUE "\001\x1b[38;5;25m\002"
# define GREEN "\001\x1b[38;5;40m\002"
# define YELLOW "\001\x1b[38;5;220m\002"
# define RES "\001\x1b[0m\002"

typedef struct s_prompt
{
	char		*message;
	char		*tb_line;
	char		*line;
}		t_prompt;

typedef struct s_cmd
{
	char		**cmd;
	char		*path;
	char		*in_file;
	char		*out_file;
	char		*delimiter;
	int			here_pipe[2];
	int			mode_in;
	int			mode_out;
	int			here_doc;
}		t_cmd;

typedef struct s_process
{
	int			**pipes;
	int			*pids;
	int			exec_pid;
	int			processes_n;
}		t_process;

typedef struct s_data
{
	t_list		*lst_env;
	t_list		*exec_data;
	t_list		*empty_vars;
	int			cmd_count;
	int			is_pipe_empty;
	int			invalid_syntax;
	int			missing_cmd;
	t_prompt	prompt;
	t_process	procs;
	int			not_found;
	int			status;
}		t_data;

extern t_data	g_data;

/* init.c functions */

void	init_prompt(t_prompt *prompt);
void	init_data(t_data *data, char **ep);

/* init_2.c funcitons */

void	init_processes(t_process *procs);
t_cmd	*cmd_init(void);

/* prompt.c functions */

void	show_prompt(t_data *data);
char	*get_host(void);
char	*update_prompt(char *prompt, char *path);
char	*update_root_prompt(char *ptr_prompt, char *abs_path);

/* prompt_utils.c functions */

void	exit_minishell(t_data *data);
void	parse_and_execute(t_data *data);
void	save_history(char *line);
char	*get_prompt(void);
char	*update_prompt_msg(t_data *data);

/* signals.c functions */

void	main_signals(void);
void	executor_signals(int pid, int f);
void	heredoc_signals(int pid, int f);

/* signals_2.c functions */

int		handle_signals(t_data *data, int status, int process, int processes_n);

/* clean.c functions */

void	clean_array(void **array);
void	clean_s_cmd(void *content);
void	clean_prompt(t_prompt *prompt);
void	clean_data(t_data *data);
void	clean_processes(t_process *procs);

/* utils.c functions */

void	ft_lstdisplay(t_list *lst);
void	ft_lstremove(t_list **lst, char *value);
void	ft_lstremove_2(t_list **lst, char *value);
t_list	*ft_lstfind(t_list *lst, char *value);
t_list	*ft_lstfind_2(t_list *lst, char *value);

/* utils_2.c functions */

char	*trim_spc(char *str);
void	clean_empty_nodes(t_list **lst);
char	*insert_var_quotes(char *str);
void	*get_declared_vars(void *content);
void	raise_error(char *msg, int errn);

/* utils_3.c functions */

char	*ft_lstfind_value(t_list *lst, char *value);
char	*get_value(char *str);
char	*get_key(char *str);
char	**get_array_from_lst(t_list *lst);
t_list	*get_lst_from_array(char **arr);

/* utils_4.c functions */

void	throw_pipe_error(int err, t_data *data);

#endif
