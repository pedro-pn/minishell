/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:52:42 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 12:49:12 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_line_lst(t_list **lst, char *line);
static void	get_variable_node(t_list **lst, char *line, int *start, int *end);
static void	expand_variables_lst(t_list *env, t_list **lst);
static char	*join_variables_lst(t_list *lst);

void	expansions(t_list *env, char **line)
{
	t_list	*line_lst;

	line_lst = NULL;
	if (check_for_variable(*line))
		return ;
	get_line_lst(&line_lst, *line);
	expand_variables_lst(env, &line_lst);
	free(*line);
	*line = join_variables_lst(line_lst);
	ft_lstclear(&line_lst, free);
}

static void	get_line_lst(t_list **lst, char *line)
{
	int	flag;
	int	start;
	int	end;

	start = 0;
	end = 0;
	flag = 0;
	while (line[end])
	{
		flag = quote_flag(line[end], flag);
		end++;
		if (line[start] == '$' && !(flag & QUOTE_S))
			get_variable_node(lst, line, &start, &end);
		else if (line[end] == 0 || (line[end] == '$' && !(flag & QUOTE_S)))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_substr(line, start, end - start)));
			start = end;
		}
	}
}

static void	get_variable_node(t_list **lst, char *line, int *start, int *end)
{
	int	flag;

	flag = 0;
	*end = *start + 1;
	if (line[*end] == '{')
		flag = 1;
	while (line[*end] != '}' && flag == 1)
		(*end)++;
	while (!ft_strchr(VAR_DELIMITER, line[*end]) && line[*end])
		(*end)++;
	if (line[*end] == '}')
		(*end)++;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(line, *start, *end - *start)));
	*start = *end;
}

static void	expand_variables_lst(t_list *env, t_list **lst)
{
	t_list	*temp;
	char	*var;
	char	*content;

	temp = *lst;
	while (temp)
	{
		content = (char *)temp->content;
		if (!ft_strcmp(content, "$"))
			;
		else if (content[0] == '$')
		{
			var = get_var_name(content);
			free(temp->content);
			get_variable(env, temp, var);
			free(var);
		}
		temp = temp->next;
	}
}

static char	*join_variables_lst(t_list *lst)
{
	char	*line;
	char	*aux;

	line = ft_strdup("");
	while (lst)
	{
		aux = line;
		line = ft_strjoin(aux, (char *)lst->content);
		free(aux);
		lst = lst->next;
	}
	return (line);
}
