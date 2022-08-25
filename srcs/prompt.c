/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/25 15:25:56 by frosa-ma         ###   ########.fr       */
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
		validate_pipes(prompt);
		printf("%s\n", prompt->line);

		parser_input(prompt->line);

		// free(prompt->line);

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
