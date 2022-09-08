/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:29:31 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/07 16:47:11 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_input(t_data *data);
static int	is_arg_between_pipes_empty(char **token);
static void	check_for_doubles(t_data *data, char *str);

void	validate_pipes(t_data *data)
{
	char	*p;

	p = data->prompt.line;
	data->prompt.line = ft_strtrim(p, " ");
	free(p);
	if (*data->prompt.line == '|')
	{
		printf(ERR_PIPE);
		data->invalid_syntax = 1;
		g_status = 2;
		return ;
	}
	if (is_arg_between_pipes_empty(ft_split(data->prompt.line, '|')))
	{
		printf(ERR_PIPE);
		data->invalid_syntax = 1;
		g_status = 2;
		return ;
	}
	check_for_doubles(data, data->prompt.line);
	if (data->is_pipe_empty)
	{
		data->prompt.tb_line = data->prompt.line;
		data->prompt.line = (char *)parse_input(data);
	}
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

static int	is_arg_between_pipes_empty(char **token)
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
		g_status = 2;
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
