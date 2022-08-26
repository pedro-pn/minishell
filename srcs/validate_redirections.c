/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:20:12 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/26 13:23:39 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// funcao ira validar entradas invalidas como:
// 		<
// 		>
// 		cat <
// 		cat >
void	validate_redirections(t_data *data)
{
	char	*str;
	char	first;
	char	last;
	char	*p;
	int		i;	

	i = -1;
	str = data->prompt.line;
	if (ft_strchr(str, '<') || ft_strchr(str, '>'))
	{
		p = data->prompt.line;
		data->prompt.line = ft_strtrim(p, " ");
		free(p);
		first = *data->prompt.line;
		if (ft_strlen(data->prompt.line) == 1 && (first == '<' || first == '>'))
		{
			raise_error(ERR_NEWL, 2);
			exit(2);
		}
		last = data->prompt.line[ft_strlen(data->prompt.line) - 1];
		if (last == '<' || last == '>')
		{
			raise_error(ERR_NEWL, 2);
			exit(2);
		}

		// Ainda estou implementando outras validacoes
		// char **token = ft_split(data->prompt.line)
	}
}
