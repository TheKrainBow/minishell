/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 22:44:00 by magostin          #+#    #+#             */
/*   Updated: 2021/06/25 14:30:11 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int		ret;

	ret = 0;
	if (cmd->args[1])
	{
		if (!ft_strisint(cmd->args[1]))
		{
			ret = 2;
			ft_putstr("minishell: exit: ");
			ft_putstr(cmd->args[1]);
			ft_putendl(" : digit argument required");
		}
		else if (cmd->args[2])
		{
			ft_putendl("minishell: exit: to many arguments");
			data->wexitstatus = 1;
			return ;
		}
		else
			ret = ft_atoi(cmd->args[1]);
	}
	ft_free_tab(cmd->args);
	ft_free_env(data);
	exit(ret);
}
