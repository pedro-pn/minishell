/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 10:23:06 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_data(t_data *data)
{
	ft_lstclear(&(data->exec_data), clean_s_cmd);
	clean_prompt(&data->prompt);
	data->is_pipe_empty = 0;
	data->cmd_count = 0;
	data->invalid_syntax = 0;
	data->missing_cmd = 0;
}

void	show_prompt(t_data *data)
{
	char	**args;

	while (1)
	{
		data->prompt.message = update_prompt_msg(data);
		data->prompt.line = readline(data->prompt.message);
		if (!data->prompt.line)
		{
			clean_prompt(&data->prompt);
			ft_putendl_fd("exit", 1);
			break ;
		}
		validate_pipes(data);
		validate_redirections(data);

		if (data->is_pipe_empty)
			save_history(data->prompt.tb_line);
		else
			save_history(data->prompt.line);

		data->exec_data = parser_input(data->prompt.line);

		// ===== builtins stuff
		args = ft_split(data->prompt.line, ' ');
		if (!args[0])
		{
			clean_array((void **)args);
			ft_lstclear(&(data->exec_data), clean_s_cmd);
			clean_prompt(&data->prompt);
			reset_data(data);
			continue ;
		}
		if (!data->invalid_syntax)
		{
			if (is_builtin(args[0]))
			{
				if (!data->missing_cmd)
					builtin_executor(args, data);
			}
			else
			{
				if (!data->missing_cmd)
					executor(data);
			}
		}
		clean_array((void **)args);
		// =====

		// ft_lstclear(&(data->exec_data), clean_s_cmd);
		// clean_prompt(&data->prompt);
		reset_data(data);
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

char	*get_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*temp;

	user = ft_strjoin(getenv("USER"), "@");
	temp = ft_strjoin(user, getenv("USERNAME"));
	free(user);
	prompt = ft_strjoin(temp, ": ");
	free(temp);
	return (prompt);
}

char	*update_prompt(char *prompt, char *path)
{
	char	*cutoff;
	char	*ptr_prompt;

	cutoff = ft_strjoin("~", path);
	ptr_prompt = prompt;
	prompt = ft_strjoin(ptr_prompt, cutoff);
	free(cutoff);
	free(ptr_prompt);
	ptr_prompt = prompt;
	prompt = ft_strjoin(ptr_prompt, "$ ");
	free(ptr_prompt);
	return (prompt);
}

char	*update_root_prompt(char *ptr_prompt, char *abs_path)
{
	char	*prompt;
	char	*temp;

	temp = ft_strjoin(ptr_prompt, abs_path);
	free(ptr_prompt);
	prompt = ft_strjoin(temp, "$ ");
	free(temp);
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
		prompt = update_prompt(prompt, path);
		free(path);
		return (prompt);
	}
	prompt = get_prompt();
	prompt = update_root_prompt(prompt, abs_path);
	return (prompt);
}
