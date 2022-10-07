/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:00:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/07 11:29:52 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_data *data)
{
	clean_data(data);
	rl_clear_history();
	ft_lstclear(&data->lst_env, free);
	ft_putendl_fd("exit", 1);
	exit(data->status);
}

void	parse_and_execute(t_data *data)
{
	check_open_var(data->prompt.line);
	if (data->invalid_syntax)
	{
		ft_putendl_fd("Invalid syntax", 2);
		return ;
	}
	expansions(data->lst_env, &data->prompt.line);
	if (ft_strlen(data->prompt.line) == 0)
		return ;
	data->exec_data = parser_input(data->prompt.line);
	data->status = executor(data);
}

/* Saves input received from prompt*/
void	save_history(char *line)
{
	if (!line)
		return ;
	while (*line)
	{
		if (*line != ' ')
		{
			add_history(line);
			return ;
		}
		line++;
	}
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*host;
	char	*p;

	user = ft_strjoin(getenv("USER"), "@");
	host = get_host();
	p = user;
	prompt = ft_strjoin(p, host);
	free(p);
	p = prompt;
	prompt = ft_strjoin(GREEN, p);
	free(p);
	p = prompt;
	prompt = ft_strjoin(p, RES);
	free(p);
	p = prompt;
	prompt = ft_strjoin(p, ":");
	free(p);
	return (prompt);
}

char	*update_prompt_msg(void)
{
	char	pwd[PATH_MAX];
	char	*home;
	char	*abs_path;
	char	*prompt;
	char	*path;

	home = getenv("HOME");
	abs_path = getcwd(pwd, PATH_MAX);
	if (ft_strnstr(abs_path, home, ft_strlen(abs_path)))
	{
		prompt = get_prompt();
		path = ft_substr(abs_path, ft_strlen(home), ft_strlen(abs_path));
		prompt = update_prompt(prompt, path);
		free(path);
		return (prompt);
	}
	prompt = get_prompt();
	prompt = update_root_prompt(prompt, abs_path);
	return (prompt);
}
