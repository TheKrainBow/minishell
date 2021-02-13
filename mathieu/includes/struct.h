/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/02/13 21:47:02 by magostin         ###   ########.fr       */
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

typedef struct				s_cmd
{
	char					**args;
}							t_cmd;

typedef struct				s_data
{
	t_gram					*lex_dict;
	int						dict_size;
	t_list					*lexed_line;
	int						ret_temp;
	char					quote;
	char					**path;
}							t_data;

#endif