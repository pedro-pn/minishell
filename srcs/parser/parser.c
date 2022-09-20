/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/20 10:11:52 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	doub_quote(char **buff, char **str, t_data *data);

static void	get_exec_data(t_cmd *exec_cont, t_list *cmd_l, t_list **exec_cmds);
static t_list	*create_exec_data(t_list *cmd_lines);
static void	create_input_list(t_list **cmd_lines, char *line);

t_list	*parser_input(t_data *data, char *line)
{
	t_list	*exec_data;
	t_list	*cmd_lines;
	t_list	*lst;
	char 	*p;

	cmd_lines = NULL;
	exec_data = NULL;
	lst = NULL;
	expand(line, &lst, data);
	// p = line;
	line = get_str_from_lst(lst);
	// free(p);
	create_input_list(&cmd_lines, line);
	exec_data = create_exec_data(cmd_lines);
	ft_lstclear(&lst, free);
	ft_lstclear(&cmd_lines, free);
	free(line);
	return (exec_data);
}

static t_list	*create_exec_data(t_list *cmd_lines)
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
		clean_empty_nodes(&exec_cmds);
		exec_cont->cmd = get_array_from_lst(exec_cmds);
		ft_lstclear(&exec_cmds, free);
		clean_quote(exec_cont);
		ft_lstadd_back(&exec_data, ft_lstnew(exec_cont));
		cmd_lines = cmd_lines->next;
	}
	return (exec_data);
}

/* Creates the linked list with the user entry properly formatted to execution*/
static void	get_exec_data(t_cmd *exec_cont, t_list *cmd_l, t_list **exec_cmds)
{
	int		end;
	int		start;
	int		flag;
	char	*cmd;

	flag = 0;
	start = 0;
	end = 0;
	cmd = ((char *)cmd_l->content);
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

/* Creates a t_list with each command separated by pipes*/
static void	create_input_list(t_list **cmd_lines, char *line)
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
