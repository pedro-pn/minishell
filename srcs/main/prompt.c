/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 14:34:46 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_host(void);

void	show_prompt(t_data *data)
{
	while (1)
	{
		data->prompt.message = update_prompt_msg(data);
		data->prompt.line = readline(data->prompt.message);
		if (!data->prompt.line)
			exit_minishell(data);
		check_open_quotes(data->prompt.line);
		validate_pipes(data);
		validate_redirections(data);
		save_history(data->prompt.line);
		if (data->invalid_syntax)
			;
		else if (*data->prompt.line)
			parse_and_execute(data);
		clean_data(data);
	}
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

static char	*get_host(void)
{
	char	*host;

	host = getenv("HOSTNAME");
	if (!host)
		host = getenv("USERNAME");
	if (!host)
		host = getenv("NAME");
	if (!host)
		host = "minishell";
	return (host);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*temp;
	char	*host;
	char	*p;

	user = ft_strjoin(getenv("USER"), "@");
	host = get_host();
	p = user;
	prompt = ft_strjoin(p, host);
	free(p);
	p = prompt;
	prompt = ft_strjoin(GREEN, p); // cor usuario
	free(p);
	p = prompt;
	prompt = ft_strjoin(p, RES);
	free(p);
	p = prompt;
	prompt = ft_strjoin(p, ":");
	free(p);
	return (prompt);
}

char	*update_prompt(char *prompt, char *path)
{
	char	*cutoff;
	char	*ptr_prompt;
	char	*p;

	cutoff = ft_strjoin("~", path);
	p = cutoff;
	cutoff = ft_strjoin(BLUE, p); // cor path
	free(p);
	p = cutoff;
	cutoff = ft_strjoin(p, RES);
	free(p);
	ptr_prompt = prompt;
	prompt = ft_strjoin(ptr_prompt, cutoff);
	free(ptr_prompt);
	free(cutoff);
	ptr_prompt = prompt;
	prompt = ft_strjoin(ptr_prompt, "$ ");
	free(ptr_prompt);
	return (prompt);
}

char	*update_root_prompt(char *ptr_prompt, char *abs_path)
{
	char	*prompt;
	char	*p;

	p = abs_path;
	abs_path = ft_strjoin(BLUE, p); // cor path (non-home)
	free(p);
	prompt = ft_strjoin(ptr_prompt, abs_path);
	free(ptr_prompt);
	free(abs_path);
	p = prompt;
	prompt = ft_strjoin(p, RES);
	free(p);
	p = prompt;
	prompt = ft_strjoin(p, "$ ");
	free(p);
	return (prompt);
}

char	*update_prompt_msg(t_data *data)
{
	char	*home;
	char	*abs_path;
	char	*prompt;
	char	*path;

	home = getenv("HOME");
	abs_path = get_value((char *)ft_lstfind(data->lst_env, "PWD")->content);
	if (ft_strnstr(abs_path, home, ft_strlen(abs_path)))
	{
		prompt = get_prompt();
		path = ft_substr(abs_path, ft_strlen(home), ft_strlen(abs_path));
		free(abs_path);
		prompt = update_prompt(prompt, path);
		free(path);
		return (prompt);
	}
	prompt = get_prompt();
	prompt = update_root_prompt(prompt, abs_path);
	return (prompt);
}
