/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 22:24:42 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/12 12:50:00 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_pipes_2(char **line)
{
	if (**line == 34)
	{
		while ((*line)++, **line)
		{
			if (**line == 34)
				break ;
			if (**line == '|')
				**line = CTRL_PIPE;
		}
		if (!**line)
			return (1);
	}
	return (0);
}

/* Handles single and double quotes in the input line*/
int	save_pipes(char *line)
{
	while (*line)
	{
		if (*line == 39)
		{
			while (line++, *line)
			{
				if (*line == 39)
					break ;
				if (*line == '|')
					*line = CTRL_PIPE;
			}
			if (!*line)
				return (1);
		}
		if (save_pipes_2(&line))
			return (1);
		line++;
	}
	return (0);
}

void	restore_pipes(char	**strs)
{
	int	index;
	int	index_2;

	index = -1;
	while (index++, strs[index])
		ft_memrpl(strs[index], CTRL_PIPE, '|', ft_strlen(strs[index]));
}