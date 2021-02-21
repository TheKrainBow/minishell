/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:04:10 by magostin          #+#    #+#             */
/*   Updated: 2021/02/21 22:31:41 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct				s_cmd
{
	char					**args;
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

/*
** type_open : '<', '>', '+' (= "">>""), '|'
*/
typedef struct		s_red
{
	char			*file_name;
	char			type_open;
	struct s_red	*next;
}					t_red;

#endif