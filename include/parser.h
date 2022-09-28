/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:53:02 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/28 17:08:25 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_data	t_data;

/* parser.c functions */

t_list	*parser_input(char *line);

/* parser_utils.c functions */

int		quote_flag(char c, int flag);
void	reset_infile(t_cmd *exec_cmds);
void	reset_outfile(t_cmd *exec_cmds);
void	get_infile(t_cmd *exec_cmds, char *cmd, int *st, int *ed);
void	get_outfile(t_cmd *exec_cmds, char *cmd, int *st, int *ed);

/* parser_quotes.c functions */

void	remove_quotes(char **str);
void	clean_quote(t_cmd *cmd);

/* parser_quotes_2.c function */

void	clean_cmds_quotes(char **cmds);
void	clean_infile_quotes(char **infile);
void	clean_outfile_quotes(char **outfile);
void	clean_delimiter_quotes(char **delimiter);
void	check_open_quotes(char *line);

/* expansion.c functions */

void	expansions(t_list *env, char **line);

/* expansion_utils.c */

int		check_for_variable(char *line);
char	*get_var_name(char *str);
void	get_variable(t_list *env, t_list *node, char *var);
void	check_open_var(char *line);

/* validate_pipes.c functions */

void	validate_pipes(t_data *data);

/* validade_redirections.c functions */

void	validate_redirections(t_data *data);

/* wildcard.c functions */

void	expand_wildcard(t_list **args);

#endif
