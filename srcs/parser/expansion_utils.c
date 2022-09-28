/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:39:37 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 11:25:55 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_variable(char *line)
{
	int	flag;
	int	index;

	flag = 0;
	index = 0;
	while (line[index])
	{
		flag = quote_flag(line[index], flag);
		if (line[index] == '$' && !(flag & QUOTE_S))
			return (0);
		index++;
	}
	return (1);
}

char	*get_var_name(char *str)
{
	int	start;
	int	end;

	start = 0;
	while (ft_strchr("${", str[start]))
		start++;
	end = start;
	while (str[end] != '}' && str[end] != 0)
		end++;
	return (ft_substr(str, start, end - start));
}

void	get_variable(t_list *env, t_list *node, char *var)
{
	char	*value;

	value = ft_lstfind_value(env, var);
	if (!ft_strcmp(var, "?"))
	{
		node->content = ft_itoa(g_data.status);
		return ;
	}
	else if (value)
		node->content = ft_strdup(value);
	else
		node->content = ft_strdup("");
}

void	check_open_var(char *line)
{
	int	flag;
	int	index;

	flag = 0;
	index = 0;
	while (line[index])
	{
		flag = quote_flag(line[index], flag);
		if (line[index] == '{' && !(flag & (QUOTE_S + OPEN_BCKT)))
			flag ^= OPEN_BCKT;
		else if (line[index] == '}' && (flag & OPEN_BCKT))
			flag ^= OPEN_BCKT;
		index++;
	}
	if (flag & 4)
		g_data.invalid_syntax = 1;
}
