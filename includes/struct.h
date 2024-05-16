/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:40:06 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/16 15:29:11 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"

typedef struct s_data
{
	t_list		*cmds;
	char		**env;
	int			last_error;
}			t_data;

typedef struct s_cmd
{
	char	*name;
	char	**args;
	char	**env;
	char	*output_file;
}	t_cmd;

#endif