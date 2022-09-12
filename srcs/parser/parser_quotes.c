/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:32:15 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/11 21:30:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_chars(char *str);

static int	handle_quotes_2(char **line)
{
	if (**line == 34)
	{
		**line = ' ';
		while ((*line)++, **line)
		{
			if (**line == 34)
			{
				**line = ' ';
				break ;
			}
			if (**line == 39)
				**line = 3;
		}
		if (!**line)
			return (1);
	}
	return (0);
}

/* Handles single and double quotes in the input line*/
static int	handle_quotes(char *line)
{
	while (*line)
	{
		if (*line == 39)
		{
			*line = ' ';
			while (line++, *line)
			{
				if (*line == 39)
				{
					*line = ' ';
					break ;
				}
				if (*line == 34)
					*line = 2;
			}
			if (!*line)
				return (1);
		}
		if (handle_quotes_2(&line))
			return (1);
		line++;
	}
	return (0);
}

/* Replaces the spaces between quotes with a control character*/
static void	save_spaces(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == ' ')
			line[index] = 1;
		index++;
	}
}

static void	restore_quote(char *str)
{
	ft_memrpl(str, 1, 32, ft_strlen(str));
	ft_memrpl(str, 2, 34, ft_strlen(str));
	ft_memrpl(str, 3, 39, ft_strlen(str));
}

static void	join_commands(char **splitted_s, char **str)
{
	int		index;
	char	*temp;

	index = 0;
	temp = ft_strdup(splitted_s[0]);
	while (index++, splitted_s[index])
	{
		free(*str);
		*str = ft_strjoin(temp, splitted_s[index]);
		free(temp);
		temp = ft_strdup(*str);
	}
	if (!splitted_s[1])
	{
		free(*str);
		*str = ft_strdup(temp);
	}
	free(temp);
}

void	remove_quotes(char **str)
{
	char	**splitted_s;
	int		index;

	index = -1;
	while (index++, str[index])
	{
		if (!ft_strchr(str[index], 34) && !ft_strchr(str[index], 39))
			continue ;
		save_spaces(str[index]);
		handle_quotes(str[index]);
		splitted_s = ft_split(str[index], ' ');
		if (splitted_s[0])
			join_commands(splitted_s, &str[index]);
		restore_quote(str[index]);
		clean_array((void **)splitted_s);
	}
}

// void	print_chars(char *str)
// {
// 	int index;

// 	index = 0;
// 	while (str[index])
// 	{
// 		ft_printf("%d\n", str[index]);
// 		index++;
// 	}
// 	ft_printf("%d\n", str[index]);
// }