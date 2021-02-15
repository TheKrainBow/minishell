/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/02/15 19:49:05 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct				s_cmd
{
	char					**args;
	int						piped;
	struct s_cmd			*next;
}							t_cmd;

typedef struct				s_debug
{
	int						term1;
	int						term2;
}							t_debug;

typedef struct				s_data
{
	t_debug					db;

	int						dict_size;
	t_list					*lexed_line;
	t_list					*parsed_line;
	int						ret_temp;
	char					quote;
	char					**path;
	int						wexitstatus;
	int						wifexited;
}							t_data;

#endif