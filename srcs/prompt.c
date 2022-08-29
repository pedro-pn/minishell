/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/29 16:42:01 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_data(t_data *data)
{
	free(data->prompt.line);
	free(data->prompt.message);
	data->is_pipe_empty = 0;
	data->cmd_count = 0;
}

/* Displays prompt on terminal*/
void	show_prompt(t_data *data)
{
	t_list	*exec_data;

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
		save_history(data->prompt.line);
		exec_data = parser_input(data->prompt.line);

		char	**args = ft_split(data->prompt.line, ' ');
		if (!args[0])
			continue ;
		if (!ft_strcmp(args[0], "echo"))
			__echo(args);
		if (!ft_strcmp(args[0], "cd"))
			__cd(args, data);
		if (!ft_strcmp(args[0], "pwd"))
			__pwd(args);
		if (!ft_strcmp(args[0], "env"))
			__env(args, data);
		if (!ft_strcmp(args[0], "export"))
			__export(args, data);
		if (!ft_strcmp(args[0], "unset"))
			__unset(args, data);
		if (!ft_strcmp(args[0], "exit"))
			exit(0);
		if (!ft_strcmp(args[0], "clear"))
			system("clear"); // so por hora

		clean_array((void **)args);

		// teste da função export
		// export((t_cmd *)exec_data->content, &(data->lst_env));
		// ft_lstdisplay(data->lst_env);
		ft_lstclear(&exec_data, clean_s_cmd);
		clean_prompt(&data->prompt);
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
	temp = ft_strjoin(user, getenv("NAME"));
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
