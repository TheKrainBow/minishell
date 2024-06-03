/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/06/01 19:12:20 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signum;

void	ft_exit(t_cmd *cmd)
{
	int		ret;

	ret = 0;
	ft_printf("exit\n");
	if (cmd->args[1])
	{
		if (!ft_strisint(cmd->args[1]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			exit(2);
		}
		else if (cmd->args[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			g_signum = 1;
			return ;
		}
		ret = ft_atoi(cmd->args[1]);
	}
	free_data(cmd->data);
	exit(ret);
}
