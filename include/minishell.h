/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:09 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/06 17:34:09 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

# define META_C "><"
# define PATH_MAX 4096

# define ERR_PIPE "-minishell: syntax error near unexpected token `|'\n"
# define ERR_NEWL "-minishell: syntax error near unexpected token `newline'\n"

extern int		g_status;

typedef struct s_prompt
{
	char		*directory;
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
}		t_data;

// init
void	init_prompt(t_prompt *prompt);
void	init_data(t_data *data, char **ep);

// prompt
void	show_prompt(t_data *data);
void	save_history(char *line);
char	*update_prompt_msg(t_data *data);

// parser
t_list	*parser_input(char *line);
t_list	*create_input_list(char	*line);
t_cmd	*cmd_init(void);
void	get_cmd(char **cmd_line, t_cmd **exec_cmds);
void	remove_quotes(char **str);

// token
char	**get_input(char *line);

// signals
void	main_signals(void);
void	executor_signals(int pid);
// void	heredoc_signals(void);
void	heredoc_signals(int pid);

// clean
void	clean_array(void **array);
void	clean_cmd_lines(void *content);
void	clean_s_cmd(void *content);
void	clean_prompt(t_prompt *prompt);
void	clean_data(t_data *data);
void	clean_processes(t_process *procs);

// validate
void	validate_pipes(t_data *data);
void	validate_redirections(t_data *data);

// builtins
int		is_builtin(t_data *data, t_cmd *exec, int process);
int		builtin_executor(t_data *data, char **cmds);
void	builtin_executor_2(t_data *data, t_cmd *exec);
int		__echo(char **args, t_data *data);
int		__cd(char **args, t_data *data);
int		__pwd(char **args);
int		__env(char **args, t_data *data);
int		__export(char **args, t_data *data);
int		__unset(char **args, t_data *data);

// executor
int		executor(t_data *data);
void	exec_init(t_data *data);
void	_exec(t_data *data, t_list *exec_data) ;
void	exec_child(t_data *data, t_cmd *exec, int process);
void	get_path(t_data *data, char **cmd, char **path);
int		get_given_path(t_data *data, char **cmd, char **path);
int		check_path(char **bin_paths, char *cmd, char **path);
int		wait_processes(t_data *data, int processes_n);
int		**get_pipes(t_data *data);
int		open_pipes(t_data *data);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes);
void	check_infile(t_data *data, t_cmd *exec, int process);
void	get_here_doc(t_cmd *exec);
void	check_outfile(t_data *data, t_cmd *exec, int process);
int		verify_infile(t_data *data, t_cmd *exec, int process);
int		verify_outfile(t_data *data, t_cmd *exec, int process);

// executor utils
int		*get_pids(t_data *data);
void	output_exec_error(t_cmd *exec);
void	expand_variables(t_data *data, t_cmd *exec);\

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

// Debbug - delete later
void	print_content(char **array);

#endif