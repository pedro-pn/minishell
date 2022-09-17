/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/17 11:36:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_content(char **array);
void	*get_exec_data(t_cmd *exec_cont, t_list *cmd_lines, t_list **exec_cmds);
static void	get_infile(t_cmd *exec_cmds, char *cmd, int *st, int *ed);
static void	get_outfile(t_cmd *exec_cmds, char *cmd, int *st, int *ed);
char	*trim_spc(char *str);
void	print_exec_data(t_list *exec_data);
t_list	*create_exec_data(t_list *cmd_lines);

/* Validates the input*/
t_list	*parser_input(t_data *data, char *line)
{
	t_list	*exec_data;
	t_list	*cmd_lines;
	t_list	*temp;

	cmd_lines = NULL;
	exec_data = NULL;
	create_input_list(&cmd_lines, line);
	exec_data = create_exec_data(cmd_lines);
//	print_exec_data(exec_data);
	ft_lstclear(&cmd_lines, free);
	return (exec_data);
}

t_list	*create_exec_data(t_list *cmd_lines)
{
	t_list	*exec_data;
	t_list	*exec_cmds;
	t_cmd	*exec_cont;
	
	exec_data = NULL;
	exec_cmds = NULL;
	while (cmd_lines)
	{
		exec_cont = cmd_init();
		get_exec_data(exec_cont, cmd_lines, &exec_cmds);
		exec_cont->cmd = get_array_from_lst(exec_cmds);
		ft_lstclear(&exec_cmds, free);
		ft_lstadd_back(&exec_data, ft_lstnew(exec_cont));
		cmd_lines = cmd_lines->next;
	}
	return (exec_data);
}

int	quote_flag(char c, int flag)
{
	if (c == '\"' && !(flag & QUOTE_S))
		flag ^= QUOTE_D;
	else if (c == '\'' && !(flag & QUOTE_D))
		flag ^= QUOTE_S;
	return (flag);
}

/* Creates the linked list with the user entry properly formatted to execution*/
void	*get_exec_data(t_cmd *exec_cont, t_list *cmd_lines, t_list **exec_cmds)
{
	int		end;
	int		start;
	int		flag;
	char	*cmd;

	flag = 0;
	start = 0;
	end = 0;
	cmd = ((char *)cmd_lines->content);
	while (cmd[end])
	{
		flag = quote_flag(cmd[end], flag);
		end++;
		if (cmd[start] == '<' && !(flag & 3))
			get_infile(exec_cont, cmd, &start, &end);
		else if (cmd[start] == '>' && !(flag & 3))
			get_outfile(exec_cont, cmd, &start, &end);
		else if ((ft_strchr(META_C, cmd[end]) || cmd[end] == 0) && !(flag & 3))
		{
			ft_lstadd_front(exec_cmds, ft_lstnew(
				trim_spc(ft_substr(cmd, start, end - start))));
			start = end + 1;
		}
	}
}


void	reset_infile(t_cmd *exec_cmds)
{
	free(exec_cmds->in_file);
	free(exec_cmds->delimiter);
	exec_cmds->in_file = NULL;
	exec_cmds->delimiter = NULL;
}

void	reset_outfile(t_cmd *exec_cmds)
{
	free(exec_cmds->out_file);
	exec_cmds->out_file = NULL;
}

/* Get input files in the user input, signalized by '<' or '<<'*/
static void	get_infile(t_cmd *exec_cmds, char *cmd, int *st, int *ed)
{
	int	flag;

	flag = 0;
	reset_infile(exec_cmds);
	*ed = *st + 1;
	if (cmd[*ed] == '<')
	{
		exec_cmds->here_doc = 1;
		(*ed)++;
	}
	if (cmd[*ed] == ' ')
		(*ed)++;
	(exec_cmds)->mode_in = O_RDONLY;
	*st = *ed;
	while (!((cmd[*ed] == ' ' && !(flag & 3)) || !cmd[*ed]))
	{
		flag = quote_flag(cmd[(*ed)], flag);
		printf("ed: %d\n", *ed);
		(*ed)++;
	}
	if (exec_cmds->here_doc == 1)
		exec_cmds->delimiter = trim_spc(ft_substr(cmd, *st, *ed - *st));
	else
		exec_cmds->in_file = trim_spc(ft_substr(cmd, *st, *ed - *st));
	*st = *ed + 1;
}

/* Get output files in the user input, signalized by '>' or '>>'*/
static void	get_outfile(t_cmd *exec_cmds, char *cmd, int *st, int *ed)
{
	int	flag;

	flag = 0;
	reset_outfile(exec_cmds);
	*ed = *st + 1;
	if (cmd[*ed] == '>')
	{	
		exec_cmds->mode_out = O_APPEND | O_CREAT | O_WRONLY;
		(*ed)++;
	}
	else
		exec_cmds->mode_out = O_CREAT | O_WRONLY | O_TRUNC;
	if (cmd[*ed] == ' ')
		(*ed)++;
	*st = *ed;
	while (!((cmd[*ed] == ' ' && !(flag & 3)) || !cmd[*ed]))
	{
		flag = quote_flag(cmd[*ed], flag);
		(*ed)++;
	}
	exec_cmds->out_file = trim_spc(ft_substr(cmd, *st, *ed - *st));
	*st = *ed + 1;
}

char	*trim_spc(char *str)
{
	char	*temp;

	temp = str;
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}

/* Creates a t_list with each command separated by pipes*/
void	create_input_list(t_list **cmd_lines, char *line)
{
	int	start;
	int end;
	int	flag;
	
	start = 0;
	end = 0;
	flag = 0;
	while (line[end])
	{
		if (line[end] == '\"' && !(flag & QUOTE_S))
			flag ^= QUOTE_D;
		else if (line[end] == '\'' && !(flag & QUOTE_D))
			flag ^= QUOTE_S;
		end++;
		if ((line[end] == '|' || line[end] == 0) && !(flag & 3))
		{
			ft_lstadd_back(cmd_lines, ft_lstnew(
				trim_spc(ft_substr(line, start, end - start))));
			start = end + 1;
		}
	}
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

void	print_exec_data(t_list *exec_data)
{
	t_cmd	*cmd;
	
	while (exec_data)
	{
		printf("=============\n");
		cmd = (t_cmd *)exec_data->content;
		print_content(cmd->cmd);
		printf("in_file: %s\n", cmd->in_file);
		printf("out_file: %s\n", cmd->out_file);
		printf("delimiter: %s\n", cmd->delimiter);
		printf("mode_in %d\n", cmd->mode_in);
		printf("mode_out: %d\n", cmd->mode_out);
		printf("here_doc: %d\n", cmd->here_doc);
		printf("=============\n");
		exec_data = exec_data->next;
	}
}