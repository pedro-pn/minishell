/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:34:45 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/19 23:48:16 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_append(char **buff, char **str);
static void	list_append_exp(char **buff, int i, char **str, t_data *data);

void	update_buffer(char **buff, char *str, t_data *data)
{
	int	i;

	if (!*str)
		return ;
	while (*str && *str != '$')
		list_append(buff, &str);
	if (*str && *str == '$')
		list_append_exp(buff, get_len(++str, 0), &str, data);
	update_buffer(buff, str, data);
}

static void	list_append(char **buff, char **str)
{
	char	*ch;
	char	*p;

	ch = ft_chtos(**str);
	p = *buff;
	*buff = ft_strjoin(p, ch);
	free(p);
	free(ch);
	(*str)++;
}

static void	list_append_exp(char **buff, int i, char **str, t_data *data)
{
	char	*key;
	char	*value;
	char	*p;

	key = ft_substr(*str, 0, i);
	value = expand_value(key, ft_lstfind(data->lst_env, key));
	free(key);
	p = *buff;
	*buff = ft_strjoin(p, value);
	free(p);
	free(value);
	while (i--)
		(*str)++;
}
