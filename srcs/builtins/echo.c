/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:29:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:25:41 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we can add one more int in ft_echo to track option position in args
//if we need in case of " | "

int	check_echo_opt(char *option)
{
	int	i;

	if (option[0] != '-' || option[1] != 'n')
		return (0);
	i = 1;
	while (option[++i])
		if (option[i] != 'n')
			return (0);
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_opt;

	i = 1;
	if (cmd->args[i] == NULL)
	{
		ft_putstr("\n");
		return ;
	}
	n_opt = check_echo_opt(cmd->args[i]);
	if (n_opt == 1 && cmd->args[i + 1] == NULL)
		return ;
	while (check_echo_opt(cmd->args[i]))
		i++;
	while (cmd->args[i] != NULL)
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (n_opt == 0)
		ft_putstr("\n");
	cmd->data->last_error = 0;
}
