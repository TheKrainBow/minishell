/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 03:08:55 by magostin          #+#    #+#             */
/*   Updated: 2021/01/26 16:50:20 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define CHAR_WSPACE 1
# define CHAR_SEMI 2
# define CHAR_PIPE 3
# define CHAR_SQUOTE 4
# define CHAR_WQUOTE 5

void		pars_line(char *str);
int			lex_line(t_data *data, char *line);


t_lex		*ft_lstnew_lexer(char *c, int s, int c_type);
void		ft_lstadd_back_lexer(t_lex **alst, t_lex *new);

#endif