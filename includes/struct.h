/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/01/24 19:08:36 by magostin         ###   ########.fr       */
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

typedef struct				s_data
{
	t_gram					*lex_dict;
}							t_data;

#endif