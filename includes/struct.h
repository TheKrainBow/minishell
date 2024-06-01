/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:40:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 14:25:25 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"

typedef enum e_token
{
	PIPE,
	OUT_TRUNCATE,
	OUT_APPEND,
	IN,
	HERE_DOC,
	WHITESPACE,
	T_NONE,
}	t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				fd;
}					t_lexer;

typedef struct s_data
{
	t_list			*cmds;
	char			**env;
	int				std_in;
	int				std_out;
	int				last_error;
}					t_data;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	t_data			*data;
	t_list			*out;
	int				pipe[2];
	int				pid;
}					t_cmd;

typedef void	(*t_func_cmd)(t_cmd *cmd);

#endif