/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:51:03 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 15:07:31 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_quotes(char *argv, int c);
static void	handle_io(char *line);
static int	verify_quotes(char *line);
static int	verify_quotes_2(char **line);

/* Gets the input line and splits it into an array.*/
char	**get_input(char *line)
{
	char	**input;
	int		index_input;

	if (verify_quotes(line))
		return (NULL); // se a condição for verdadeira, há aspas simples ou dupla aberta;
	clean_quotes(line, 39);
	clean_quotes(line, 34);
	handle_io(line);
	input = ft_split(line, ' ');
	index_input = -1;
	while (index_input++, input[index_input])
	{
		ft_memrpl(input[index_input], 1, 32, ft_strlen(input[index_input]));
		ft_memrpl(input[index_input], 2, 34, ft_strlen(input[index_input]));
		ft_memrpl(input[index_input], 3, 39, ft_strlen(input[index_input]));
	}
	return (input);
}

static int	verify_quotes_2(char **line)
{
	if (**line == 34)
	{
		while ((*line)++, **line)
		{
			if (**line == 34)
				break ;
			if (**line == 39)
				**line = 3;
		}
		if (!**line)
			return (1);
	}
	return (0);
}

/* Handles single and double quotes in the input line*/
static int	verify_quotes(char *line)
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
					*line = 2;
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
static void	clean_quotes(char *line, int c)
{
	int	index;
	int	flag;

	index = 0;
	flag = 1;
	while (line[index])
	{
		if (line[index] == c)
			flag *= -1;
		else if (flag == -1)
		{
			if (line[index] == ' ')
				line[index] = 1;
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
			line[index + 1] = 1;
		else if (line[index] == '<' && line[index + 1] == ' ')
			line[index + 1] = 1;
		index++;
	}
}