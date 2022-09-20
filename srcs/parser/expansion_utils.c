/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:37:00 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/19 23:44:56 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exp(t_exp *exp, t_list **lst, t_data *data)
{
	exp->lst = lst;
	exp->data = data;
	exp->buff = ft_strdup("");
}

int	get_len(char *s, int flag)
{
	int	i;

	i = 0;
	if (flag == 0)
		while (s[i] && s[i] != ' ' && s[i] != '$')
			i++;
	else if (flag == 1)
		while (s[i] && s[i] != ' ' && s[i] != '$' && s[i] != '"' && s[i] != 39)
			i++;
	else
		while (s[i] != '"')
			i++;
	return (i);
}

void	populate_list_with_buffer(int i, char **str, char *buff, t_list **lst)
{
	while (*buff)
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*buff++)));
	while (i--)
		(*str)++;
}

// Nao estou usando por hora
int	is_dollar_sign_only(char *str)
{
	char	*prompt;

	if (!str)
		return (1);
	prompt = ft_strtrim(str, " ");
	if (ft_strlen(prompt) == 1 && *prompt == '$')
		return (free(prompt), 1);
	return (free(prompt), 0);
}
