/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:18:16 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/17 13:11:38 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_temp(char **temp, char **cmd);
static char	*ft_chtos(char ch);
static void	fill_buffer(t_exp *exp, char **buffer, char **cmd, int mode);
static char	*alloc_whspc_str(int i);

void	quoted_expansion(char *cmd, t_data *data, char **buffer)
{
	t_exp	exp;
	char	*temp;

	exp.data = data;
	if (!*cmd)
		return ;
	exp.temp = ft_strdup("");
	if (*cmd != '$')
		init_temp(&exp.temp, &cmd);
	exp.var = ++cmd;
	exp.i = 0;
	while (exp.var[exp.i] != '$' && exp.var[exp.i] != ' ' \
		&& exp.var[exp.i] != '"' && exp.var[exp.i])
		exp.i++;
	if (exp.var[exp.i] == '$')
		fill_buffer(&exp, buffer, &cmd, 1);
	else
		fill_buffer(&exp, buffer, &cmd, 0);
}

static void	init_temp(char **temp, char **cmd)
{
	char	*ch;
	char	*pb;

	while (**cmd != '$' && **cmd)
	{
		ch = ft_chtos(**cmd);
		pb = *temp;
		*temp = ft_strjoin(pb, ch);
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

static char	*alloc_whspc_str(int i)
{
	char	*str;

	str = (char *)malloc(i + 1 * sizeof(char));
	ft_memset(str, ' ', i);
	str[i] = 0;
	return (str);
}

static void	fill_buffer(t_exp *exp, char **buffer, char **cmd, int mode)
{
	char	*spaces;
	char	*pb;

	if (mode == 1)
	{
		expand(exp, buffer);
		while (**cmd != ' ' && **cmd != '$')
			(*cmd)++;
		quoted_expansion(*cmd, exp->data, buffer);
	}
	else
	{
		expand(exp, buffer);
		while (**cmd != ' ' && **cmd)
			(*cmd)++;
		exp->i = 0;
		while (*(*cmd)++ == ' ' && **cmd)
			exp->i++;
		spaces = alloc_whspc_str(exp->i);
		pb = *buffer;
		*buffer = ft_strjoin(pb, spaces);
		free(pb);
		free(spaces);
		quoted_expansion(--(*cmd), exp->data, buffer);
	}
}
