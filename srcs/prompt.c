/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/29 12:14:18 by ppaulo-d         ###   ########.fr       */
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
		data->prompt.message = update_message(data->prompt.directory);
		data->prompt.line = readline(data->prompt.message);
		if (!data->prompt.line)
		{
			clean_prompt(&data->prompt);
			ft_putendl_fd("exit", 1);
			break ;
		}
		validate_pipes(data);
		validate_redirections(data);
		save_line(data->prompt.line);
		exec_data = parser_input(data->prompt.line);

		// teste da função export e unset
		export((t_cmd *)exec_data->content, &(data->lst_env));
		if (!ft_strcmp((((t_cmd *)exec_data->content)->cmd)[0], "unset"))
			unset((t_cmd *)exec_data->content, &(data->lst_env));
		ft_lstdisplay(data->lst_env);
		ft_lstclear(&exec_data, clean_s_cmd);
		clean_prompt(&data->prompt);
		// reset_data(data);
	}
}

/* Saves input received from prompt*/
void	save_line(char *line)
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

/* Returns the message to display in prompt*/
char	*update_message(char *dir)
{
	char	*message;
	char	*temp;

	message = ft_strjoin("minishell: ", dir);
	temp = message;
	message = ft_strjoin(temp, "$ ");
	free(temp);
	return (message);
}
