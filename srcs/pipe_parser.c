/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:49:59 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/25 15:26:01 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function receive that single piped array of strings and returns a parsed str
// 		{"ls |", " ls |", "ls|"}  ->  "ls | ls | ls"
char	*get_parsed_str(char **parsed)
{
	char	*str;
	char	*p;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (parsed[i])
	{
		p = str;
		str = ft_strjoin(p, parsed[i]);
		free(p);
		i++;
	}
	p = str;
	str = ft_strtrim(p, "|");
	free(p);
	return (str);
}

// This functions insert a single pipe between each command (last one inclusive)
// 		{"ls", "ls", "ls"}  ->  {"ls |", " ls |", "ls|"}
char	**get_parsed_pipe_args(char **arr)
{
	char	**parsed;
	char	*last;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	parsed = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!parsed)
		exit(1); // TODO: handle
	i = 0;
	while (*arr)
		parsed[i++] = ft_strjoin(*arr++, "|");
	return (parsed);
}

// Checks for error where user provide empty command between pipes
// 		ls |     | ls
int	is_arg_between_pipes_empty(char **args)
{
	char	*temp;
	int 	i;

	i = 0;
	while (args[i])
	{
		temp = ft_strtrim(args[i], " ");
		if (ft_strlen(temp) == 0)
			return (1);
		free(temp);
		i++;
	}
	return (0);
}

// Checks whether the input start/ends with a pipe
// 		|, |ls, ls||, ls||ls|, ls||ls|| 
void	check_first_and_last(char *str)
{
	if (*str == '|')
	{
		ft_putendl_fd("-msh: Syntax error near unexpected token `|'", 2); // handle
		exit(2);
	}
	if (str[ft_strlen(str) - 2] == '|')
	{
		if (str[ft_strlen(str) - 1] == '|')
		{
			// TODO: any command after a double pipe is ignored (i.e  echo foo || echo bar | echo baz  ) -> foo
			ft_putendl_fd("Double pipe detected", 2); 
			exit(2);
		}
	}
}

// This function may remove duplicated pipes and check for input errors: 
//    ls || ls ->  ls | ls
//    |, ||, ls|, |ls, ls||, ls||ls, ...
char	*parse_pipes(char *str) 
{
	char	**parsed; 
	char	**args;

	check_first_and_last(str); // check  |, |ls, ls||, ls||ls|, ls||ls|| 

	args = (char **)ft_split(str, '|'); // {"ls", "ls", "ls"}
	free(str);

	if (is_arg_between_pipes_empty(args))
	{
		ft_putendl_fd("-msh: Syntax error near unexpected token `|'", 2); // handle
		exit(2);
	}

	parsed = (char **)get_parsed_pipe_args(args); // {"ls |", " ls |", " ls|"}
	free_split(args);

	str = (char *)get_parsed_str(parsed); // "ls | ls | ls"
	free_split(parsed);
	return (str);
}

void	validate_pipes(t_prompt *prompt) // "   ls || ls || ls      "
{
	char	*p;

	p = prompt->line;
	prompt->line = ft_strtrim(p, " ");
	free(p);
	prompt->line = parse_pipes(prompt->line); // "ls | ls | ls"
}
