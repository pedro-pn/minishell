/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:51:03 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/12 12:04:54 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_io(char *line);

/* Gets the input line and splits it into an array.*/
char	**get_input(char *line)
{
	char	**input;

	if (verify_quotes(line))
		return (NULL); // se a condição for verdadeira, há aspas simples ou dupla aberta;
	handle_quoted_args(line);
	handle_io(line);
	input = ft_split(line, ' ');
	restore_quotes(input);
	return (input);
}

int	verify_quotes_2(char **line)
{
	if (**line == 34)
	{
		while ((*line)++, **line)
		{
			if (**line == 34)
				break ;
			if (**line == 39)
				**line = CTRL_S;
		}
		if (!**line)
			return (1);
	}
	return (0);
}

/* Handles single and double quotes in the input line*/
int	verify_quotes(char *line)
{
	while (*line)
	{
		if (*line == 39)
		{
			while (line++, *line)
			{
				if (*line == 39)
					break ;
				if (*line == 34)
					*line = CTRL_D;
			}
			if (!*line)
				return (1);
		}
		if (verify_quotes_2(&line))
			return (1);
		line++;
	}
	return (0);
}

/* Replaces the spaces between quotes with a control character*/
void	clean_quotes(char *line, int quote, int c, int ctrl)
{
	int	index;
	int	flag;

	index = 0;
	flag = 1;
	while (line[index])
	{
		if (line[index] == quote)
			flag *= -1;
		else if (flag == -1)
		{
			if (line[index] == c)
				line[index] = ctrl;
		}
		index++;
	}
}

/* Replaces the spaces after input/output characters with a control character*/
static void handle_io(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '>' && line[index + 1] == ' ')
			line[index + 1] = CTRL_SPC;
		else if (line[index] == '<' && line[index + 1] == ' ')
			line[index + 1] = CTRL_SPC;
		index++;
	}
}
