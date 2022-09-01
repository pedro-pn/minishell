/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:20:12 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/01 08:28:28 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verify_file_existence_and_permission(t_data *data);
static void	verify_num_args(t_data *data);

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
			// g_status = 2;
			return ;
		}
		ch = data->prompt.line[ft_strlen(data->prompt.line) - 1];
		if (ch == '<' || ch == '>')
		{
			printf(ERR_NEWL);
			data->invalid_syntax = 1;
			// g_status = 2;
			return ;
		}
		verify_file_existence_and_permission(data);
		verify_num_args(data);
	}
}

static void	verify_file_existence_and_permission(t_data *data)
{
	char	**tokens;
	char	*file;
	int		i;
	
	tokens = ft_split(data->prompt.line, ' ');
	if (!ft_strcmp(tokens[0], "<<"))
		return ;
	if (tokens[0][0] == '<')
	{
		file = tokens[1];
		if (access(file, F_OK))
		{
			printf("-minishell: %s: No such file or directory\n", file);
			data->invalid_syntax = 1;
			// g_status = 1;
		}
		else if (access(tokens[1], R_OK))
		{
			printf("-minishell: %s: Permission denied\n", file);
			data->invalid_syntax = 1;
			// g_status = 1;
		}
	}
	clean_array((void **)tokens);
}

static void	verify_num_args(t_data *data)
{
	char	**tokens;
	int		i;
	
	tokens = ft_split(data->prompt.line, ' ');
	i = 0;
	while (tokens[i])
		i++;
	if (!tokens[2])
		data->missing_cmd = 1;
	clean_array((void **)tokens);
}
