/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:07:38 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/17 13:13:27 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prev_str(char **cmd);
static char	*get_result(char *var, int i, char *str, t_data *data);

void	simple_expansion(char *cmd, t_data *data, char **s)
{
	char	*result;
	char	*str;
	char	*var;
	char	*pb;
	int		i;

	if (!*cmd)
		return ;
	str = get_prev_str(&cmd);
	var = ++cmd;
	i = 0;
	while (var[i] != '$' && var[i])
		i++;
	result = get_result(var, i, str, data);
	free(str);
	while (*cmd != '$' && *cmd)
		cmd++;
	pb = *s;
	*s = ft_strjoin(pb, result);
	free(pb);
	free(result);
	simple_expansion(cmd, data, s);
}

static char	*get_prev_str(char **cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (*(*cmd + i) != '$')
		i++;
	str = ft_substr(*cmd, 0, i);
	while (**cmd != '$')
		*(*cmd)++;
	return (str);
}

static char	*get_result(char *var, int i, char *str, t_data *data)
{
	char	*to_find;
	char	*value;
	char	*result;

	to_find = ft_substr(var, 0, i);
	value = get_value_expansion(to_find, ft_lstfind(data->lst_env, to_find));
	free(to_find);
	result = ft_strjoin(str, value);
	free(value);
	return (result);
}
