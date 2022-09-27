/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:29:31 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/26 23:00:07 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_pipe(char *prompt, t_data *data);
static void	toggle_quoted_pipes(char *s);
static int	is_pipe_empty(char **token);
static void	pipe_check(char *s, t_data *data);
static void	throw_pipe_error(int err, t_data *data);
static void	check_for_doubles(t_data *data, char *str);

void	validate_pipes(t_data *data)
{
	char	*prompt;

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
		} else if (*s == '\'')
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
	int 	i;

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

static void	throw_pipe_error(int err, t_data *data)
{
	if (err == 1)
		printf("-minishell: syntax error near unexpected token `|'\n");
	else if (err == 2)
		printf("-minishell: syntax error near unexpected token `||'\n");
	data->invalid_syntax = 1;
	data->status = 2;
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

// pode ser usado para verificar se ha `||` no prompt 
static void	check_for_doubles(t_data *data, char *str)
{
	int		count;
	char	*p;

	if (!str)
		return ;
	p = ft_strchr(str, '|');
	if (!p)
		return ;
	count = 0;
	while (p && *p++ == '|')
		count++;
	if (count > 2)
	{
		printf(ERR_PIPE);
		data->invalid_syntax = 1;
		data->status = 2;
		return ;
	}
	data->cmd_count++;
	if (count == 2)
	{
		data->is_pipe_empty = 1;
		return ;
	}
	check_for_doubles(data, p);
}
