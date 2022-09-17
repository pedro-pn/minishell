/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/17 20:35:31 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	doub_quote(char **buff, char **str, t_data *data);

void			print_content(char **array);
static t_list	*get_exec_data(t_data *data, t_list *cmd_lines);
static void		get_infile(char **cmd_line, t_cmd **exec_cmds);
static void		get_outfile(char **cmd_line, t_cmd **exec_cmds);

// fn
// is_dollar_only
// chtos

char	*ft_chtos(char ch)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	*str = ch;
	return (str);
}

int	is_dollar_only(char *str)
{
	char	*prompt;

	if (!str)
		return (1);
	prompt = ft_strtrim(str, " ");
	if (ft_strlen(prompt) == 1 && *prompt == '$')
		return (free(prompt), 1);
	return (free(prompt), 0);
}



void	sing_quote(char **buff, char *str)
{
	static int flag;
	flag = 0;

	if (!*str)
		return ;
	if (*str == '\'')
		flag++;
	if (flag == 2)
		return ;

	if (is_dollar_only(str))
	{
		*buff = ft_strtrim(str, " ");
		return ;
	}

	char *ch;
	char *p;

	ch = ft_chtos(*str++);
	p = *buff;
	*buff = ft_strjoin(p, ch);
	free(p);
	free(ch);
	sing_quote(buff, str);
}

void	do_that(char **buff, char **str, t_data *data)
{
	char	*ch;
	char	*pb;

	while (**str != '$' && **str != '\'')
	{
		ch = ft_chtos(**str);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
		free(ch);
		free(pb);
		(*str)++;
	}
}
void	do_this(char **buff, char **str, t_data *data)
{
	char *ch;
	char *pb;

	ch = ft_chtos(**str);
	pb = *buff;
	*buff = ft_strjoin(pb, ch);
	free(ch);
	free(pb);
	(*str)++;
	while (**str != '\'')
	{
		ch = ft_chtos(**str);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
		free(ch);
		free(pb);
		(*str)++;
	}
	ch = ft_chtos(**str);
	pb = *buff;
	*buff = ft_strjoin(pb, ch);
	free(ch);
	free(pb);
	(*str)++;
}
void	doub_quote(char **buff, char **str, t_data *data)
{
	if (!**str)
		return ;

	// single `$` checker
	// char *y;
	// y = ft_strtrim(str, " ");
	// if (ft_strlen(y) == 1 && *y == '$')
	// {
	// 	*buff = ft_strtrim(str, " ");
	// 	free(y);
	// 	return ;
	// }
	// free(y);

	char	*ch;
	char	*pb;

	char	*temp;
	temp = ft_strdup("");
	if (**str == '\'')
	{
		ch = ft_chtos(**str);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
		free(ch);
		free(pb);
		*(*str)++;
		while (**str != '\'')
		{
			ch = ft_chtos(**str);
			pb = *buff;
			*buff = ft_strjoin(pb, ch);
			free(ch);
			free(pb);
			*(*str)++;
		}
		ch = ft_chtos(**str);
		pb = *buff;
		*buff = ft_strjoin(pb, ch);
		free(ch);
		free(pb);
		*(*str)++;
	}
	if (**str != '$')
	{
		while (**str != '$' && **str != '\'')
		{
			ch = ft_chtos(**str);
			pb = *buff;
			*buff = ft_strjoin(pb, ch);
			free(ch);
			free(pb);
			*(*str)++;
		}
	}
	if (**str == '$')
	{
		*(*str)++;

		// verificar o tamanho do nome da variavel ambiente e expandi-la
		int i;
		i = 0;
		while (*str[i] != '$' && *str[i] != ' ' && *str[i] != '\'' && *str[i] != '"' && *str[i])
			i++;
		t_list *node;
		char *var;
		char *value;
		var = ft_substr(*str, 0, i);
		node = ft_lstfind(data->lst_env, var);
		value = get_value_expansion(var, node);
		free(var);

		// modificar o buffer
		char *p;
		p = *buff;
		*buff = ft_strjoin(p, value);
		free(p);
		free(value);

		// mover o pointer
		while (i--)
			*(*str)++;
		*(*str)++;
	}
	doub_quote(buff, str, data);
}

void	disp(t_list *lst)
{
	char	*buff;
	char	*pb;

	buff = malloc((ft_lstsize(lst) + 1) * sizeof(char));
	pb = buff;
	while (lst)
	{
		*buff++ = *(char *)lst->content;
		lst = lst->next;
	}
	*buff = 0;
	printf("%s\n", pb);
}

void	expn(char **buff, char *str, t_data *data)
{
	if (!*str)
		return ;
	while (*str && *str != '$')
	{
		char	*ch;
		char	*p;
		ch = ft_chtos(*str);
		p = *buff;
		*buff = ft_strjoin(p, ch);
		free(p);
		free(ch);
		str++;
	}
	if (*str && *str == '$')
	{
		char	*p;
		char	*s;
		char	*v;
		int 	i;

		str++;
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '$')
			i++;
		s = ft_substr(str, 0, i);
		v = get_value_expansion(s, ft_lstfind(data->lst_env, s));
		free(s);
		p = *buff;
		*buff = ft_strjoin(p, v);
		free(p);
		free(v);
		while (i--)
			str++;
	}
	expn(buff, str, data);
}

void	fn(char *str, t_list **lst, t_data *data)
{
	char	*buff;
	char	*pb;

	if (!*str)
		return ;

	buff = ft_strdup(""); // string entre aspas duplas sera inserida aqui nesse buffer

	char *s;
	int i;
	if (*str == '\'')
	{
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str))); // insere ' inicial
		str++;
		while (*str != '\'')
			ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str++)));
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str++))); // insere ' final
	}
	if (*str == '$')
	{
		str++;
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"' && str[i] != '\'')
			i++;
		s = ft_substr(str, 0, i);
		char *v = get_value_expansion(s, ft_lstfind(data->lst_env, s));
		free(s);
		char *p;
		p = buff;
		buff = ft_strjoin(p, v);
		free(p);
		free(v);
		pb = buff;
		while (*pb)
			ft_lstadd_back(lst, ft_lstnew(ft_chtos(*pb++)));
		while (i--)
			str++;
	}
	if (*str != '$' && *str != '"')
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str)));
	if (*str == '"')
	{
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str))); // insere " inicial
		str++;
		i = 0;
		while (str[i] != '"')
			i++;
		s = ft_substr(str, 0, i); //  cria a string que esta entre as aspas
		expn(&buff, s, data);     //  insere a expansao dentro do buffer
		free(s);
		pb = buff;
		while (*pb)
			ft_lstadd_back(lst, ft_lstnew(ft_chtos(*pb++)));
		while (i--)
			str++;
		ft_lstadd_back(lst, ft_lstnew(ft_chtos(*str))); // insere " final
	}
	free(buff);
	fn(++str, lst, data);
}

char	*get_str_from_lst(t_list *lst)
{
	char	*str;
	char	*p;

	str = (char *)malloc((ft_lstsize(lst) + 1) * sizeof(char));
	p = str;
	while (lst)
	{
		*p++ = *(char *)lst->content;
		lst = lst->next;
	}
	return (str);
}

t_list	*parser_input(t_data *data, char *line)
{
	t_list	*exec_data;
	t_list	*cmd_lines;
	char 	*p;

	t_list	*lst;
	lst = NULL;
	fn(line, &lst, data);
	// disp(lst);

	p = line;
	line = get_str_from_lst(lst);
	free(p);
	ft_lstclear(&lst, free);

	printf("%s\n", line);
	free(line);
	exit(0);

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
		// expand_variables(data, exec_cmds);
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
