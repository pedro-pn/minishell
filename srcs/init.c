/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:38 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/25 15:41:35 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes prompt struct variables*/
void	prompt_init(t_prompt *prompt)
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
void	update_stdio_fds(t_data *data)
{
	// Faz uma copia dos fds de saida padrao
	data->bk_stdin = dup(STDIN_FILENO);   // 0 -> 3
	data->bk_stdout = dup(STDOUT_FILENO); // 1 -> 4
	data->bk_stderr = dup(STDERR_FILENO); // 2 -> 5

	// Fecha os fds herdados (i.e. 0, 1, 2)
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Cria os fds de saida padrao para o novo processo (main) usando os fds temporarios
	dup2(data->bk_stdin, STDIN_FILENO);   // 3 -> 0
	dup2(data->bk_stdout, STDOUT_FILENO); // 4 -> 1
	dup2(data->bk_stderr, STDERR_FILENO); // 5 -> 2

	// Fecha os fds temporarios
	close(data->bk_stdin);
	close(data->bk_stdout);
	close(data->bk_stderr);
}

void	update_SHLVL(t_data *data)
{
	char	*str;
	char	*p;
	int		value;
	int 	i;

	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], "SHLVL", 5))
		{
			str = ft_strrchr(data->env[i], '=') + 1;
			value = ft_atoi(str) + 1;
			free(data->env[i]);
			p = ft_itoa(value);
			data->env[i] = ft_strjoin("SHLVL=", p);
			free(p);
		}
	}
}

static char	**get_environment(char **ep)
{
	char	**envp;
	int		i;

	i = 0;
	while (ep[i])
		i++;
	envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (*ep)
		envp[i++] = ft_strdup(*ep++);
	return (envp);
}

void	data_init(t_data *data, char **ep)
{
	char	*builtins;

	builtins = "echo cd pwd env export unset exit";
	data->builtins = ft_split(builtins, ' ');

	data->env = (char **)get_environment(ep);
	update_SHLVL(data);     // 1 -> 2

	update_stdio_fds(data); // 0 1 2  ->  3 4 5  ->  0 1 2
}
