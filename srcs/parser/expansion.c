/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:35:32 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/20 10:56:48 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_append(char **str, t_list **lst);
static void	list_append_exp(char **str, int i, char **buff, t_exp *exp);
static void	quoted_expansion(char **str, char **buff, t_exp *exp);
static int	get_quoted_len(char *s);

void	expand(char *str, t_list **lst, t_data *data)
{
	t_exp	exp;

	if (!*str)
		return ;
	init_exp(&exp, lst, data);
	if (*str == '\'')
	{
		list_append(&str, exp.lst);
		expand(str, exp.lst, exp.data);
		free(exp.buff);
		return ;
	}
	if (*str == '$')
	{
		list_append_exp(&str, get_len(++str, 1), &exp.buff, &exp);
		expand(str, exp.lst, exp.data);
		free(exp.buff);
		return ;
	}
	if (*str != '$' && *str != '"')
		ft_lstadd_back(exp.lst, ft_lstnew(ft_chtos(*str)));
	if (*str == '"')
		quoted_expansion(&str, &exp.buff, &exp);
	free(exp.buff);
	expand(++str, exp.lst, exp.data);
}

static void	list_append(char **str, t_list **lst)
{
	ft_lstadd_back(lst, ft_lstnew(ft_chtos(**str)));
	(*str)++;
	while (**str != '\'')
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*(*str)++)));
	ft_lstadd_back(lst, ft_lstnew(ft_chtos(*(*str)++)));
}

static void	list_append_exp(char **str, int i, char **buff, t_exp *exp)
{
	char	*key;
	char	*value;
	char	*p;

	key = ft_substr(*str, 0, i);
	value = expand_value(key, ft_lstfind(exp->data->lst_env, key));
	free(key);
	p = *buff;
	*buff = ft_strjoin(p, value);
	free(p);
	free(value);
	populate_list_with_buffer(i, str, *buff, exp->lst);
}

static int	get_quoted_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '"')
		i++;
	return (i);
}

static void	quoted_expansion(char **str, char **buff, t_exp *exp)
{
	char	*s;

	ft_lstadd_back(exp->lst, ft_lstnew(ft_chtos(*(*str)++)));
	s = ft_substr(*str, 0, get_quoted_len(*str));
	update_buffer(buff, s, exp->data);
	free(s);
	populate_list_with_buffer(get_len(*str, 2), str, *buff, exp->lst);
	ft_lstadd_back(exp->lst, ft_lstnew(ft_chtos(**str)));
}
