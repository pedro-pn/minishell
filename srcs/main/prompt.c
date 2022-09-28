/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 05:39:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_host(void)
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

char	*update_prompt(char *prompt, char *path)
{
	char	*cutoff;
	char	*ptr_prompt;
	char	*p;

	cutoff = ft_strjoin("~", path);
	p = cutoff;
	cutoff = ft_strjoin(BLUE, p);
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
	abs_path = ft_strjoin(BLUE, p);
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
