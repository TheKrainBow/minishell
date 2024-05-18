/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:28:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/18 03:54:30 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "libft.h"

/*         Built-ins                       */
int		ft_cd(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);

/*         Parsing                          */
int		parse_input(t_data *data, char *input);

/*        Parsing/lexer/lexer.c             */
t_list	*input_lexer(char *input);

/*        Parsing/lexer/token.c             */
char	*token_to_strs(t_token token);
t_token	get_token(char *str);
int		check_tokens(t_list **tokens);

/*        Parsing/lexer/quote.c             */
int		skip_quotes(char *input);
int		ft_isquote(char c);

/*        Parsing/lst.c                     */
char	*lst_conv(void *content);
int		is_pipe(void *content);
int		is_arg(void *content);

/*       Parsing/memory.c                   */
void	free_cmd(void *ptr);
void	free_lexer(void *ptr);
t_data	*init_data(char **environ);
void	free_data(t_data *data);

#endif