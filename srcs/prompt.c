/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 13:47:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Displays prompt on terminal*/
void	show_prompt(t_prompt *prompt)
{
	char	*message;
	//t_list	*exec_data;

	while (1)
	{
		message = update_message(prompt->directory);
		prompt->line = readline(message);
		if (!prompt->line)
		{
			ft_putendl_fd("exit", 1); // ctl D handler
			break ;
		}
		save_line(prompt->line);
		parser_input(prompt->line);
		free(prompt->line);
		// Provavelmente esse loop vai ser  o principal e todo o projeto
		// será executado a partir daqui. Por isso é interessante deixar ele
		// com poquissimas tarefas.
		free(message);
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

/* Initializes prompt struct variables*/
void	prompt_init(t_prompt *prompt)
{
	prompt->line = NULL;
	prompt->directory = getcwd(NULL, 0);
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
