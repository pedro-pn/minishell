/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:53:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/14 13:26:12 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(char **buff, char *cmd, t_data *data);
static char	*simple_expansion(char *cmd, t_data *data);
static char	*quoted_expansion(char *cmd, t_data *data);
static void	fill_buffer(char **buff, char **cmd);
static char	*ft_chtos(char ch);
static char	*_get_value(char *key, t_list *node);

void	expand_variables(t_data *data, t_cmd *exec)
{
	char	*buff;
	int		i;

	if (!exec->cmd)
		return ;
	if (check_first_cmd(exec->cmd[0]) || !ft_strcmp(exec->cmd[0], "awk"))
		return ;
	i = 0;
	buff = ft_strjoin(exec->cmd[0], " ");
	while (exec->cmd[++i])
	{
		if (ft_strchr(exec->cmd[i], '$'))
			expand(&buff, exec->cmd[i], data);
		else
			if (*exec->cmd[i])
				buff = parse_cmd(buff, exec->cmd[i]);
	}
	clean_array((void **)exec->cmd);
	verify_quotes(buff);
	clean_quotes(buff, 39, 32, CTRL_SPC);
	clean_quotes(buff, 34, 32, CTRL_SPC);
	exec->cmd = ft_split(buff, ' ');
	free(buff);
	restore_quotes(exec->cmd);
}

static void	expand(char **buff, char *cmd, t_data *data)
{
	char	*str;
	char	*pb;

	pb = *buff;
	if (*cmd == '\'')
	{
		*buff = parse_cmd(*buff, cmd);
		return ;
	}
	if (*cmd != '"')
	{
		str = simple_expansion(cmd, data);
		*buff = ft_strjoin(pb, str);
	}
	else
	{
		str = quoted_expansion(cmd, data);
		*buff = ft_strjoin(pb, str);
	}
	free(pb);
	free(str);
}

static char	*simple_expansion(char *cmd, t_data *data)
{
	t_list	*node;
	char	*result;
	char	*str;
	char	*value;
	char	*var;
	int		i;

	i = 0;
	while (cmd[i] != '$')
		i++;
	str = ft_substr(cmd, 0, i);
	var = ft_strchr(cmd, '$') + 1;
	node = ft_lstfind(data->lst_env, var);
	value = _get_value(var, node);
	var = value;
	value = ft_strjoin(var, " ");
	free(var);
	result = ft_strjoin(str, value);
	free(str);
	free(value);
	return (result);
}

static char	*quoted_expansion(char *cmd, t_data *data)
{
	char	*temp;
	char	*p;
	char	*value;
	char	*str;

	temp = ft_strdup("");
	if (*cmd != '$')
		fill_buffer(&temp, &cmd);
	p = ft_strtrim(++cmd, "\"");
	value = _get_value(p, ft_lstfind(data->lst_env, p));
	free(p);
	p = value;
	value = ft_strjoin(p, "\" ");
	free(p);
	str = ft_strjoin(temp, value);
	free(temp);
	free(value);
	return (str);
}

static void	fill_buffer(char **buff, char **cmd)
{
	char	*ch;
	char	*pb;

	while (**cmd != '$' && **cmd)
	{
		ch = ft_chtos(**cmd);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
		free(ch);
		free(pb);
		(*cmd)++;
	}
}

static char	*ft_chtos(char ch)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	*str = ch;
	return (str);
}

static char	*_get_value(char *key, t_list *node)
{
	char	*value;

	value = NULL;
	if (*key == '?')
		value = ft_itoa(g_status);
	else if (!node)
		value = ft_strdup("");
	else
		value = get_value((char *)node->content);
	return (value);
}
