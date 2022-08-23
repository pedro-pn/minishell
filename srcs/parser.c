/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:18:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/23 19:51:57 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Validates the input*/
int	parser_input(char *line)
{
	char	**input;

	input = get_input(line);
	if (!input)
		return (1);
		
	/* Aqui virão as próximas funções de parsing (validar comando, atribuição
	de variáveis, here_doc, infile, etc...)*/

	/*Este loop é só pra teste, printa cada linha retornada pela função anterior*/
	for (int i = 0; input[i]; i++){
		printf("%s\n", input[i]);
	}
	return (0);
}
