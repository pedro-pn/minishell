/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:46 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/23 14:14:37 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_prompt	prompt;
	// Essa estrutura muito provavelmente vai ficar dentro
	// de outra estrutura maior, pois caso o usuario mude
	// o diretório de trabalho, basta atualizá-la.
	prompt_init(&prompt);
	show_prompt(&prompt);
	return (0);
}