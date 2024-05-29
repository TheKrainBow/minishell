/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:28:21 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 04:12:08 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
# include "struct.h"
# include "libft.h"

/*         Built-ins                       */
void	ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_execve(t_cmd *cmd);

int		plus_in_name(char *env_name);
int		already_in_env(char *env_name, t_cmd *cmd);
int		check_env_name(char *env_name);
void	remove_plus(char *str);
char	*get_var_from_env(char **env, char *var);

/*         Utils/signal.c                   */
void	signals_main(void);
void	signals_pipe(void);

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
void	swap_quote(char *quote, char c);
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
