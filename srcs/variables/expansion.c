/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:52:42 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/19 19:37:35 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_variable(char *line);
void	get_line_lst(t_list **lst, char *line);
void	get_variable_node(t_list **lst, char *line, int *start, int *end);

void	expansions(char	*line)
{
	t_list	*line_lst;

	line_lst = NULL;
	if (check_for_variable(line))
		return ;
	get_line_lst(&line_lst, line);
	ft_lstdisplay(line_lst);
	//exit(0);
}

int	check_for_variable(char *line)
{
	int flag;
	int	index;

	flag = 0;
	index = 0;
	while (line[index])
	{
		flag = quote_flag(line[index], flag);
		if (line[index] == '$' && !(flag & QUOTE_S))
		{
			if (line[index + 1] == ' ' || line[index + 1] == 0)
				return (1);
		}
		index++;
	}
	return (0);
}

void	get_line_lst(t_list **lst, char *line)
{
	int		flag;
	int		start;
	int		end;

	start = 0;
	end = 0;
	flag = 0;
	while (line[end])
	{
		flag = quote_flag(line[end], flag);
		end++;
		if (line [start] == '$' && !(flag & QUOTE_S))
			get_variable_node(lst, line, &start, &end);
		else if (line[end] == 0 || (line[end] == '$' && !(flag & QUOTE_S)))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_substr(line, start, end - start)));
			start = end;
		}
	}
}
#define QUOTE_LIMITER "$\"\'}|>< "
void	get_variable_node(t_list **lst, char *line, int *start, int *end)
{
	while (!ft_strchr(QUOTE_LIMITER, line[*end]) && line[*end])
		(*end)++;
	if (line[*end] == '}')
		(*end)++;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(line, *start, *end - *start)));
	*start = *end;
}