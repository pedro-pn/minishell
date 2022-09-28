/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:20:12 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/28 05:47:48 by coder            ###   ########.fr       */
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
			ft_putendl_fd(ERR_NEWL, 2);
			data->invalid_syntax = 1;
			data->status = 2;
			return ;
		}
		ch = data->prompt.line[ft_strlen(data->prompt.line) - 1];
		if (ch == '<' || ch == '>')
		{
			ft_putendl_fd(ERR_NEWL, 2);
			data->invalid_syntax = 1;
			data->status = 2;
			return ;
		}
	}
}
