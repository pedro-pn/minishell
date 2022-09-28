/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:29:31 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/28 05:34:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_pipe(char *prompt, t_data *data);
static void	toggle_quoted_pipes(char *s);
static int	is_pipe_empty(char **token);
static void	pipe_check(char *s, t_data *data);

void	validate_pipes(t_data *data)
{
	char	*prompt;

	if (data->invalid_syntax)
		return ;
	prompt = ft_strtrim(data->prompt.line, " ");
	if (*prompt == '|')
	{
		invalid_pipe(prompt, data);
		free(prompt);
		return ;
	}
	toggle_quoted_pipes(prompt);
	if (is_pipe_empty(ft_split(prompt, '|')))
	{
		throw_pipe_error(1, data);
		free(prompt);
		return ;
	}
	if (!ft_strchr(prompt, '|'))
	{
		free(prompt);
		return ;
	}
	pipe_check(prompt, data);
	free(prompt);
}

static void	invalid_pipe(char *prompt, t_data *data)
{
	if (*(prompt + 1) == '|')
		throw_pipe_error(2, data);
	else
		throw_pipe_error(1, data);
}

static void	toggle_quoted_pipes(char *s)
{
	while (*s)
	{
		if (*s == '"')
		{
			s++;
			while (*s != '"')
			{
				if (*s == '|')
					*s = 3;
				s++;
			}
		}
		else if (*s == '\'')
		{
			s++;
			while (*s != '\'')
			{
				if (*s == '|')
					*s = 3;
				s++;
			}
		}
		s++;
	}
}

static int	is_pipe_empty(char **token)
{
	char	*str;
	int		i;

	i = 0;
	while (token[i])
	{
		str = ft_strtrim(token[i], " ");
		if (ft_strlen(str) == 0)
		{
			clean_array((void **)token);
			free(str);
			return (1);
		}
		free(str);
		i++;
	}
	clean_array((void **)token);
	return (0);
}

static void	pipe_check(char *s, t_data *data)
{
	int	i;

	if (!*s)
		return ;
	i = 0;
	while (s[i] == '|')
		i++;
	if (i > 2)
	{
		if (i == 3)
			throw_pipe_error(1, data);
		else
			throw_pipe_error(2, data);
		return ;
	}
	if (*s != '|')
		s++;
	else
		while (i--)
			s++;
	pipe_check(s, data);
}
