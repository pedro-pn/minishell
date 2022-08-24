/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 14:10:39 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content(char **array);

/* Initializes struct s_cmds*/
void	cmd_init(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->mode = 0;
	cmd->here_doc = 0;
}

/* Validates the input*/
t_list	*parser_input(char *line)
{
	//t_list	*exec_data;
	t_list	*cmd_lines;

	cmd_lines = create_input_list(line);
	
	/*Este loop é só pra teste, printa cada nó da t_list retornada pela função
	anterior*/
	// t_list *temp = cmd_lines;
	// while (temp)
	// {
	// 	ft_printf("new node:\n");
	// 	print_content(((char **)temp->content));
	// 	temp = temp->next;
	// }
	/* Aqui virão as próximas funções de parsing (validar comando, atribuição
	de variáveis, here_doc, infile, etc...)*/
	ft_lstclear(&cmd_lines, clean_cmd_lines);
	return (0);
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