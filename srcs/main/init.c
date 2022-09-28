/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 11:54:57 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shell(t_data *data);
static void	update_shlvl(t_data *data);

/* Initializes prompt struct variables*/
void	init_prompt(t_prompt *prompt)
{
	char	*cwd;
	
	cwd = (char *)malloc(PATH_MAX * sizeof(char));
	ft_bzero(cwd, PATH_MAX);
	prompt->line = NULL;
	prompt->tb_line = NULL;
	getcwd(cwd, PATH_MAX);
	prompt->directory = cwd;
}

//                                    bash                    minishell
// Update standard file descriptors (0, 1, 2) -> (3, 4, 5) -> (0, 1, 2)
static void	update_stdio_fds(void)
{
	int	bk_stdin;
	int	bk_stdout;
	int	bk_stderr;

	bk_stdin = dup(STDIN_FILENO);
	bk_stdout = dup(STDOUT_FILENO);
	bk_stderr = dup(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	dup2(bk_stdin, STDIN_FILENO);
	dup2(bk_stdout, STDOUT_FILENO);
	dup2(bk_stderr, STDERR_FILENO);
	close(bk_stdin);
	close(bk_stdout);
	close(bk_stderr);
}

void	init_data(t_data *data, char **ep)
{
	data->lst_env = (t_list *)get_lst_from_array(ep);
	data->empty_vars = NULL;
	update_shell(data);
	update_shlvl(data);
	update_stdio_fds();
	data->exec_data = NULL;
	data->cmd_count = 0;
	data->status = 0;
	data->is_pipe_empty = 0;
	data->invalid_syntax = 0;
	data->not_found = 0;
	init_prompt(&data->prompt);
	init_processes(&data->procs);
}

static void	update_shell(t_data *data)
{
	t_list	*node;
	char	cwd[PATH_MAX];
	char	*key;
	char	*value;
	char	*p;

	node = ft_lstfind(data->lst_env, "SHELL");
	key = get_key((char *)node->content);
	getcwd(cwd, PATH_MAX);
	value = ft_strjoin("=", cwd);
	p = value;
	value = ft_strjoin(p, "/minishell");
	free(p);
	free(node->content);
	node->content = ft_strjoin(key, value);
	free(key);
	free(value);
}

static void	update_shlvl(t_data *data)
{
	t_list	*node;
	char	*key;
	char	*value;
	char	*p;

	node = ft_lstfind(data->lst_env, "SHLVL");
	key = get_key((char *)node->content);
	value = get_value((char *)node->content);
	p = value;
	value = ft_itoa(ft_atoi(p) + 1);
	free(p);
	p = value;
	value = ft_strjoin("=", p);
	free(p);
	free(node->content);
	node->content = ft_strjoin(key, value);
	free(key);
	free(value);
}
