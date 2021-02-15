/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 03:08:55 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 16:31:20 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define CHAR_WSPACE 1
# define CHAR_SEMI 2
# define CHAR_PIPE 3
# define CHAR_SQUOTE 4
# define CHAR_WQUOTE 5

void		lex_line(char *line, t_data *data);
void		pars_line(t_data *data);
void		ft_print_pars_line(t_data *data);

#endif