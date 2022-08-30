/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/29 20:34:44 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_SHLVL(t_data *data);

/* Initializes prompt struct variables*/
void	init_prompt(t_prompt *prompt)
{
	prompt->line = NULL;
	prompt->directory = getcwd(NULL, 0);
}

/* Initializes struct s_cmds*/
t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->delimiter = NULL;
	cmd->mode = 0;
	cmd->here_doc = 0;
	return (cmd);
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
	// const char	*builtins = "echo cd pwd env export unset exit";

	// data->builtins = (char **)ft_split(builtins, ' ');
	data->lst_env = (t_list *)get_lst_from_array(ep);
	data->empty_vars = NULL;
	update_SHLVL(data);
	update_stdio_fds();

	data->cmd_count = 0;
	data->is_pipe_empty = 0;
	init_prompt(&data->prompt);
}

static void	update_SHLVL(t_data *data)
{
	t_list	*node;
	char	*key;
	char	*value;
	char	*new_value;
	char	*pk;
	char	*pv;

	node = ft_lstfind(data->lst_env, "SHLVL");
	key = get_key((char *)node->content);
	value = get_value((char *)node->content);
	new_value = ft_itoa(ft_atoi(value) + 1);
	pk = ft_strjoin(key, "=");
	free(node->content);
	free(key);
	pv = ft_strjoin(pk, new_value);
	free(pk);
	free(new_value);
	node->content = ft_strdup(pv);
	free(pv);
}
