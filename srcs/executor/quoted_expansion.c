/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:18:16 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/15 14:58:43 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_buffer(char **buff, char **cmd);
static char	*ft_chtos(char ch);

void	quoted_expansion(char *cmd, t_data *data, char **s)
{
	char	*temp;
	char	*p;
	char	*value;
	char	*result;

	printf("%s\n", *s);
	if (!*cmd)
		return ;
	temp = ft_strdup("");
	if (*cmd != '$')
		fill_buffer(&temp, &cmd);

	// printf("%s\n", temp);   "foo
	// printf("%s\n", cmd);    $NAME$HOME"

	char	*pb;
	char	*var;
	char	*to_find;
	char	*spaces;
	int 	i;

	var = ++cmd;
	i = 0;
	while (var[i] != '$' && var[i] != ' ' && var[i] != '"' && var[i])
		i++;
	if (var[i] == '$')
	{
		to_find = ft_substr(var, 0, i);
		value = _get_value(p, ft_lstfind(data->lst_env, to_find)); // DESKTOP-123
		result = ft_strjoin(temp, value); // "fooDESKTOP-123
		free(temp);
		free(value);
		pb = *s;
		*s = ft_strjoin(pb, result);
		free(pb);
		quoted_expansion(cmd, data, s);
	}
	else
	{
		to_find = ft_substr(var, 0, i);

		value = _get_value(p, ft_lstfind(data->lst_env, to_find)); // DESKTOP-123

		result = ft_strjoin(temp, value); // "fooDESKTOP-123
		free(temp);
		free(value);

		pb = *s;
		*s = ft_strjoin(pb, result);
		free(pb);

		while (*cmd != ' ' && *cmd)
			cmd++;
		i = 0;
		while (*cmd++ == ' ' && *cmd)
			i++;
		spaces = (char *)malloc(i + 1 * sizeof(char));
		ft_memset(spaces, ' ', i);
		spaces[i] = 0;

		pb = *s;
		*s = ft_strjoin(pb, spaces); // "fooDESKTOP-123   -
		free(pb);

		--cmd;
		quoted_expansion(cmd, data, s);
	}
}

static void	fill_buffer(char **buff, char **cmd)
{
	char	*ch;
	char	*pb;

	while (**cmd != '$' && **cmd)
	{
		ch = ft_chtos(**cmd);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
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
