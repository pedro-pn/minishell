/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:12:46 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/25 15:41:14 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_data		data;

	// Essa estrutura muito provavelmente vai ficar dentro
	// de outra estrutura maior, pois caso o usuario mude
	// o diretório de trabalho, basta atualizá-la.
	signals_setup();
	data_init(&data, envp);
	prompt_init(&prompt);
	show_prompt(&prompt);
	return (0);
}