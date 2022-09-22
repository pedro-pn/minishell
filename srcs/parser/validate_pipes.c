/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:29:31 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/22 12:41:12 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_input(t_data *data);
static int	is_pipe_empty(char **token);
static void	throw_error(char *prompt, int err, t_data *data);
static void	check_for_doubles(t_data *data, char *str);

void	validate_pipes(t_data *data)
{
	char	*prompt;
	char	*p;
	int		err;

	prompt = ft_strtrim(data->prompt.line, " ");
	err = is_pipe_empty(ft_split(prompt, '|'));
	if (!ft_strcmp(prompt, "|") || !ft_strcmp(prompt, "||") || err)
	{
		throw_error(prompt, err, data);
		free(prompt);
		return ;
	}
	p = ft_strtrim(prompt, "|");
	if (ft_strlen(prompt) > 2 && !ft_strlen(p))
	{
		throw_error(prompt, 2, data);
		free(prompt);
		free(p);
		return ;
	}
	free(prompt);
	free(p);
}

static char	*parse_input(t_data *data)
{
	char	**token;
	char	*str;
	char	*p;
	char	*q;
	int		i;

	str = ft_strdup("");
	token = (char **)ft_split(data->prompt.line, '|');
	i = -1;
	while (++i < data->cmd_count)
	{
		p = ft_strjoin(token[i], "|");
		q = str;
		str = ft_strjoin(q, p);
		free(q);
		free(p);
	}
	p = str;
	str = ft_strtrim(p, "|");
	free(p);
	return (str);
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

static void	throw_error(char *prompt, int err, t_data *data)
{
	if (err == 2)
		printf("-minishell: syntax error near unexpected token `||'\n");
	else if (err == 1)
		printf("-minishell: syntax error near unexpected token `|'\n");
	else
		printf("-minishell: syntax error near unexpected token `%s'\n", prompt);
	data->invalid_syntax = 1;
	data->status = 2;
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
