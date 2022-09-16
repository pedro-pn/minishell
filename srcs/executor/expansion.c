/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:53:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/15 22:56:35 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(char **buff, char *cmd, t_data *data);

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
	char	*s;
	char	*str;
	char	*pb;
	char	*p;

	pb = *buff;
	s = ft_strdup("");
	if (*cmd == '\'')
	{
		*buff = parse_cmd(*buff, cmd);
		return ;
	}
	if (*cmd != '"')
	{
		simple_expansion(cmd, data, &s);
		p = s;
		s = ft_strjoin(p, " ");
		free(p);
		*buff = ft_strjoin(pb, s);
		free(s);
	}
	else
	{
		quoted_expansion(cmd, data, &s);
		*buff = ft_strjoin(pb, s);
		free(s);
	}
	free(pb);
}
