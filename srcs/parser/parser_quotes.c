/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:08:00 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/22 11:30:39 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **str)
{
	char	*string;
	char	*temp;
	t_list	*strings;
	t_list	*head;

	strings = create_unquoted_list(*str);
	string = ft_strdup("");
	head = strings;
	while (strings)
	{
		temp = string;
		string = ft_strjoin(temp, (char *)strings->content);
		free(temp);
		strings = strings->next;
	}
	ft_lstclear(&head, free);
	free(*str);
	*str = string;
}

void	clean_single_quote(t_list **strings, char *str, int *start, int *end)
{
	(*start)++;
	while (str[*end] != '\'' && str[*end])
		(*end)++;
	ft_lstadd_back(strings, ft_lstnew(ft_substr(str, *start, *end - *start)));
	*start = *end + 1;
}

void	clean_double_quote(t_list **strings, char *str, int *start, int *end)
{
	(*start)++;
	while (str[*end] != '\"' && str[*end])
		(*end)++;
	ft_lstadd_back(strings, ft_lstnew(ft_substr(str, *start, *end - *start)));
	*start = *end + 1;
}

t_list	*create_unquoted_list(char *str)
{
	t_list	*strings;
	int		end;
	int		start;

	start = 0;
	end = 0;
	strings = NULL;
	while (str[end])
	{
		end++;
		if (str[start] == '\'')
			clean_single_quote(&strings, str, &start, &end);
		else if (str[start] == '\"')
			clean_double_quote(&strings, str, &start, &end);
		else if ((ft_strchr("\'\"", str[end]) || str[end] == 0))
		{
			ft_lstadd_back(&strings, ft_lstnew(
					ft_substr(str, start, end - start)));
			start = end + 1;
		}
	}
	return (strings);
}

void	clean_quote(t_cmd *cmd)
{
	clean_cmds_quotes(cmd->cmd);
	clean_infile_quotes(&cmd->in_file);
	clean_outfile_quotes(&cmd->out_file);
	clean_delimiter_quotes(&cmd->delimiter);
}
