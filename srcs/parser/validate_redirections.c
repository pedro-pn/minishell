/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:20:12 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/20 17:28:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_redirections(t_data *data)
{
	char	ch;
	char	*p;
	
	if (ft_strchr(data->prompt.line, '<') || ft_strchr(data->prompt.line, '>'))
	{
		p = data->prompt.line;
		data->prompt.line = ft_strtrim(p, " ");
		free(p);
		ch = *data->prompt.line;
		if (ft_strlen(data->prompt.line) == 1 && (ch == '<' || ch == '>'))
		{
			printf(ERR_NEWL);
			data->invalid_syntax = 1;
			data->status = 2;
			return ;
		}
		ch = data->prompt.line[ft_strlen(data->prompt.line) - 1];
		if (ch == '<' || ch == '>')
		{
			printf(ERR_NEWL);
			data->invalid_syntax = 1;
			data->status = 2;
			return ;
		}
	}
}
