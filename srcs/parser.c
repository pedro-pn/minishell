/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 19:16:13 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content(char **array);
t_list	*get_exec_data(t_list *cmd_lines);
void	get_infile(char **cmd_line, t_cmd **exec_cmds);
void	get_outfile(char **cmd_line, t_cmd **exec_cmds);

/* Validates the input*/
t_list	*parser_input(char *line)
{
	t_list	*exec_data;
	t_list	*cmd_lines;

	cmd_lines = create_input_list(line);
	exec_data = get_exec_data(cmd_lines);
	/*Este loop é só pra teste, printa cada nó da t_list retornada pela função
	anterior*/
	/* Aqui virão as próximas funções de parsing (validar comando, atribuição
	de variáveis, here_doc, infile, etc...)*/
	ft_lstclear(&cmd_lines, clean_cmd_lines);
	return (0);
}

t_list	*get_exec_data(t_list *cmd_lines)
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
		ft_lstadd_back(&exec_data, ft_lstnew(exec_cmds));
		cmd_lines = cmd_lines->next;
	}
	return (exec_data);
}

void	get_infile(char **cmd_line, t_cmd **exec_cmds)
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
				(*exec_cmds)->mode = O_RDONLY;
				in_address++;
			}
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

void	get_outfile(char **cmd_line, t_cmd **exec_cmds)
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
			(*exec_cmds)->mode = O_TRUNC | O_CREAT | O_WRONLY; // acho que o ideal é já abrir/criar o arquivo
			if (*in_address == '>')	// se executar no bash "echo teste > a > b" ele cria ambos os arquivos
			{						// a e b,  porém só escreve "teste" no arquivo b.
				(*exec_cmds)->mode = O_APPEND | O_CREAT | O_WRONLY; // idem
				in_address++;
			}
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
	int		index;

	cmd_lines = NULL;
	inputs = ft_split(line, '|');
	if (!inputs)
		return (NULL);
	index = -1;
	while (index++, inputs[index])
	{
		ft_lstadd_back(&cmd_lines, ft_lstnew(get_input(inputs[index])));
		free(inputs[index]);
	}
	free(inputs);
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