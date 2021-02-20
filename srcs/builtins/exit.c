/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:44:00 by magostin          #+#    #+#             */
/*   Updated: 2021/02/20 22:48:06 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_exit(t_cmd *cmd, t_data *data)
{
	ft_free_list(data->parsed_line);
	ft_free_tab(cmd->args);
	ft_free_env();
	exit (1);
}