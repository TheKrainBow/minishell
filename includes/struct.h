/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/01/25 09:31:49 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

typedef struct				s_gram
{
	char					*c;
	int						s;
	int						c_type;
}							t_gram;

typedef struct				s_lex
{
	t_gram					content;
	struct s_lex			*next;
}							t_lex;

typedef struct				s_data
{
	t_gram					*lex_dict;
	t_list					*lexed_line;
}							t_data;

#endif