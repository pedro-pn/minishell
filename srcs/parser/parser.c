/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/15 11:14:05 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_content(char **array);
static t_list	*get_exec_data(t_data *data, t_list *cmd_lines);
static void		get_infile(char **cmd_line, t_cmd **exec_cmds);
static void		get_outfile(char **cmd_line, t_cmd **exec_cmds);

/* Validates the input*/
t_list	*parser_input(t_data *data, char *line)
{
	t_list	*exec_data;
	t_list	*cmd_lines;

	cmd_lines = create_input_list(line);
	exec_data = get_exec_data(data, cmd_lines);
	ft_lstclear(&cmd_lines, clean_cmd_lines);
	return (exec_data);
}

/* Creates the linked list with the user entry properly formatted to execution*/
static t_list	*get_exec_data(t_data *data, t_list *cmd_lines)
{
	char	**content;
	t_list	*exec_data;
	t_cmd	*exec_cmds;

	exec_data = NULL;
	while (cmd_lines)
	{
		content = (char **)cmd_lines->content;
		exec_cmds = cmd_init();
		get_infile(content , &exec_cmds);
		get_outfile(content, &exec_cmds);
		get_cmd(content, &exec_cmds);
		restore_io_quoted(exec_cmds->cmd);
		expand_variables(data, exec_cmds);
		remove_quotes(exec_cmds->cmd);
		ft_lstadd_back(&exec_data, ft_lstnew(exec_cmds));
		cmd_lines = cmd_lines->next;
	}
	return (exec_data);
}

/* Get input files in the user input, signalized by '<' or '<<'*/
static void	get_infile(char **cmd_line, t_cmd **exec_cmds)
{
	char	*in_address;
	int		index;

	index = 0;
	while (cmd_line[index])
	{
		in_address = ft_strchr(cmd_line[index], '<');
		if (in_address)
		{
			in_address++;
			if (*in_address == '<')
			{
				(*exec_cmds)->here_doc = 1;
				in_address++;
			}
			(*exec_cmds)->mode_in = O_RDONLY;
			if (*in_address == ' ')
				in_address++;
			if ((*exec_cmds)->here_doc == 1)
				(*exec_cmds)->delimiter = ft_strdup(in_address);
			else
				(*exec_cmds)->in_file = ft_strdup(in_address);
		}
		index++;
	}
}

/* Get output files in the user input, signalized by '>' or '>>'*/
static void	get_outfile(char **cmd_line, t_cmd **exec_cmds)
{
	char	*in_address;
	int		index;

	index = 0;
	while (cmd_line[index])
	{
		in_address = ft_strchr(cmd_line[index], '>');
		if (in_address)
		{
			in_address++;
			if (*in_address == '>')
			{
				(*exec_cmds)->mode_out = O_APPEND | O_CREAT | O_WRONLY;
				in_address++;
			}
			else
				(*exec_cmds)->mode_out = O_CREAT | O_WRONLY | O_TRUNC;
			if (*in_address == ' ')
				in_address++;
			(*exec_cmds)->out_file = ft_strdup(in_address);
		}
		index++;
	}
}

/* Creates a t_list with each command separated by pipes*/
t_list	*create_input_list(char	*line)
{
	char	**inputs;
	t_list	*cmd_lines;
	void	*content;
	int		index;

	cmd_lines = NULL;
	save_pipes(line);
	inputs = ft_split(line, '|');
	restore_pipes(inputs);
	if (!inputs)
		return (NULL);
	index = -1;
	while (index++, inputs[index])
	{
		content = get_input(inputs[index]);
		if (!content)
		{
			ft_lstclear(&cmd_lines, clean_s_cmd);
			ft_putendl_fd("Invalid syntax", 1);
			break ;
		}
		ft_lstadd_back(&cmd_lines, ft_lstnew(content));
	}
	clean_array((void **) inputs);
	return (cmd_lines);
}

/* Função de teste para printar arrays, será deletada*/
void	print_content(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		ft_printf("%s\n", array[index]);
		index++;
	}
}
