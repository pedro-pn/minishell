/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:53:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/17 13:11:53 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_buffer(char **buff, char *cmd, t_data *data);
static void	prep_next(char *str, char *pb, char **buff);

void	expand_variables(t_data *data, t_cmd *exec)
{
	char	*buff;
	int		i;

	if (!exec->cmd)
		return ;
	if (check_first_cmd(exec->cmd[0]) || !ft_strcmp(exec->cmd[0], "awk"))
		return ;
	i = -1;
	buff = ft_strdup("");
	while (exec->cmd[++i])
	{
		if (ft_strchr(exec->cmd[i], '$'))
			init_buffer(&buff, exec->cmd[i], data);
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

static void	init_buffer(char **buff, char *cmd, t_data *data)
{
	char	*str;
	char	*pb;

	pb = *buff;
	str = ft_strdup("");
	if (*cmd == '\'')
	{
		*buff = parse_cmd(*buff, cmd);
		return ;
	}
	if (*cmd != '"')
	{
		simple_expansion(cmd, data, &str);
		prep_next(str, pb, buff);
		return ;
	}
	quoted_expansion(cmd, data, &str);
	prep_next(str, pb, buff);
}

static void	prep_next(char *str, char *pb, char **buff)
{
	char	*p;

	p = str;
	str = ft_strjoin(p, " ");
	free(p);
	*buff = ft_strjoin(pb, str);
	free(str);
	free(pb);
}

void	expand(t_exp *exp, char **buffer)
{
	t_list	*node;
	char	*to_find;
	char	*value;
	char	*result;
	char	*pb;

	to_find = ft_substr(exp->var, 0, exp->i);
	node = ft_lstfind(exp->data->lst_env, to_find);
	value = get_value_expansion(to_find, node);
	free(to_find);
	result = ft_strjoin(exp->temp, value);
	free(exp->temp);
	free(value);
	pb = *buffer;
	*buffer = ft_strjoin(pb, result);
	free(pb);
	free(result);
}
