/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:33:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/23 14:15:36 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Displays prompt on terminal*/
void	show_prompt(t_prompt *prompt)
{
	char	*message;

	while (1)
	{
		message = update_message(prompt->directory);
		prompt->line = readline(message);
		save_line(prompt->line);
		// Provavelmente esse loop vai ser  o principal e todo o projeto
		// será executado a partir daqui. Por isso é interessante deixar ele
		// com poquissimas tarefas.
		free(message);
	}
}

/* Saves input received from prompt*/
void	save_line(char *line)
{
	int	index;

	index = 0;
	if (!line)
		return ;
	while (line[index]) // Foi a maneira mais simples que achei de não salvar linhas vazias
	{					// pode conter bug, não foi testado o suficiente
		if (line[index] != ' ')
		{
			add_history(line);
			return ;
		}
		index++;
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
