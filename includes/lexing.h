/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 03:08:55 by magostin          #+#    #+#             */
/*   Updated: 2021/01/22 12:05:33 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define CHAR_WSPACE 1
# define CHAR_SEMI 2

void		pars_line(char *str);
int			lex_line(t_data *data, char *line);

#endif